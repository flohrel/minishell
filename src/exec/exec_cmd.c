/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:05:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/05/31 19:34:12 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_vars *vars, char **envp)
{
	t_param	*param;
	char	**args;

	param = vars->parser.exec_tree->data;
	args = list_to_tab(param->arg, vars);
	find_builtin(param->path, args, vars);
	find_cmd(param->path, args, envp, vars);
	return (0);
}
