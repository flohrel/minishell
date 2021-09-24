/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:22:25 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/24 18:11:04 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_fd(t_param *param)
{
	t_io	*io;

	io = &(param->io);
	pipe_handle(io);
	redir_handle(io);
	close_handle(io);
	return (1);
}

static int	find_builtin_next(char *path, char **args, t_vars *vars,
		t_param *param)
{
	int		ret;

	if (ft_strcmp("env", path) == 0 && check_fd(param))
		return (print_env(args, vars));
	else if (ft_strcmp("export", path) == 0 && check_fd(param))
	{
		ret = export(args, vars);
		handle_assign_export(vars, args, param->assign);
		return (ret);
	}
	else if (ft_strcmp("exit", path) == 0 && check_fd(param))
		return (exit_b(args, vars, param));
	return (-1);
}

int	find_builtin(char *path, char **args, t_vars *vars, t_param *param)
{
	if (!path || !args || !vars)
		return (-1);
	if (ft_strcmp("echo", path) == 0 && check_fd(param))
		return (my_echo(args, vars));
	else if (ft_strcmp("cd", path) == 0 && check_fd(param))
		return (cd(args, vars));
	else if (ft_strcmp("pwd", path) == 0 && check_fd(param))
		return (pwd(args, vars));
	else if (ft_strcmp("unset", path) == 0 && check_fd(param))
		return (unset(args, vars));
	return (find_builtin_next(path, args, vars, param));
}
