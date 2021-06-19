/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/15 15:23:17 by flohrel          ###   ########.fr       */
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

void	exec_command(t_vars *vars, t_ast *node)
{
	t_param	*param;
	char	**args;

	param = node->data;
	args = list_to_tab(param->arg, vars);
/*	if (find_builtin(param->path, args, vars))
		return ;
	else if (find_cmd(param->path, args,
				env_to_tab(vars->env, vars), vars))
		return ;*/
}

void	exec_pipeline(t_vars *vars, t_ast *node)
{
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
	if (node->type == NODE_SEQ && node->right)
		exec_cmdline(vars, node->right);
	if (node->left)
		exec_job(vars, node->left);
	else if (node)
		exec_job(vars, node);
}

void	exec_ast(t_vars *vars, t_ast *root)
{
	exec_cmdline(vars, root);
}
