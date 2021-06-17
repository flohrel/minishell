/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/17 19:20:23 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_vars *vars, t_ast *node)
{
	t_param	*param;
	char	**args;
	t_env	*res;

	param = node->data;
	args = list_to_tab(param->arg, vars);
	res = malloc(sizeof(t_env));
	if (!res)
		return (0);
	if (new_envblock(param->path, res) > 0)
	{
		handle_assign(res, vars);
		return (1);
	}
	free(res);
	if (find_builtin(param->path, args, vars))
		return (2);
	else if (find_cmd(param->path, args,
				env_to_tab(vars->env, vars), vars))
		return (3);
	return (-1);
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
	{
		exec_cmdline(vars, node->right);
	}
	if (node->left)
		exec_job(vars, node->left);
	else if (node)
		exec_job(vars, node);
}

void	exec_ast(t_vars *vars, t_ast *root)
{
	exec_cmdline(vars, root);
}
