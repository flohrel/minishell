/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:22:25 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/21 04:22:27 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_fd(t_vars *vars, t_param *param)
{
	pipe_handle(vars);
	close_handle(vars);
	redir_handle(vars, param, &vars->cmd);
	return (1);
}

static int	find_builtin_next(char *path, char **args, t_vars *vars,
		t_param *param)
{
	if (ft_strcmp("env", path) == 0 && check_fd(vars, param))
		return (print_env(args, vars));
	else if (ft_strcmp("export", path) == 0 && check_fd(vars, param))
		return (export(args, vars));
	else if (ft_strcmp("exit", path) == 0 && check_fd(vars, param))
		return (exit_b(args, vars));
	return (-1);
}

int	find_builtin(char *path, char **args, t_vars *vars, t_param *param)
{
	if (!path || !args || !vars)
		return (-1);
	if (ft_strcmp("echo", path) == 0 && check_fd(vars, param))
		return (my_echo(args, vars));
	else if (ft_strcmp("cd", path) == 0 && check_fd(vars, param))
		return (cd(args, vars));
	else if (ft_strcmp("pwd", path) == 0 && check_fd(vars, param))
		return (pwd(args, vars));
	else if (ft_strcmp("unset", path) == 0 && check_fd(vars, param))
		return (unset(args, vars));
	return (find_builtin_next(path, args, vars, param));
}
