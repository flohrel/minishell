/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/29 01:03:02 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir(t_param *param, t_rd *redir)
{
	t_list	*lst;
	t_token	*token;

	redir->field = 0;
	lst = param->redir;
	if (lst == NULL)
		return ;
	while (lst)
	{
		token = (t_token *)lst->content;
		if (token->type == TK_LESS)
		{
			set_flag(&redir->field, RD_IN);
			redir->fd_in = open(token->data, O_RDONLY);
		}
		lst = lst->next;
	}
}

void	init_cmd(t_vars *vars, t_param *param)
{
	t_cmd	*cmd;

	cmd = lst_alloc(1, sizeof(*cmd), vars);
	parse_redir(param, &cmd.redir);
}

int	exec_command(t_vars *vars, t_ast *node)
{
	t_param	*param;
	char	**args;

	param = node->data;
	args = list_to_tab(param->arg, vars);
	if (param && !(param->path))
		handle_assign(vars, param->assign);
	if (find_builtin(param->path, args, vars))
		return (1);
	if (find_cmd(param, args,
		env_to_tab(vars->env, vars), vars))
		return (3);
	return (-1);
}

void	exec_pipeline(t_vars *vars, t_ast *node)
{
	//créer le pipe, connecter le stdout de node left avec le stdin de node left de node righ si node right = pipe ou node right directement si node right = job
	//executer node->left
	//executer node->right
	//echo | echo | echo
	//if (node->right && node->right->type == NODE_PIPE)
	//	exec_pipeline(node->right);
	//else if (node->right)
	//	exec_command(node->right);
	(void)vars;
	(void)node;
}

void	exec_job(t_vars *vars, t_ast *node)
{
	if (node->type == NODE_PIPE)
		exec_pipeline(vars, node);
	else
		exec_command(vars, node);
}

void	exec_cmdline(t_vars *vars, t_ast *node)
{
	init_cmd(&vars->cmd);
	if (node->left)
		exec_job(vars, node->left);
	else if (node)
		exec_job(vars, node);
	if (node->type == NODE_SEQ && node->right)
	{
		exec_cmdline(vars, node->right);
	}
}

void	exec_ast(t_vars *vars, t_ast *root)
{
	(void)vars;
	(void)root;
	exec_cmdline(vars, root);
}
