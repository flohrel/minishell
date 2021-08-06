/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_next.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 02:57:13 by mtogbe            #+#    #+#             */
/*   Updated: 2021/08/06 16:24:09 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	errormsg(char *str, char *arg)
{
	if (str)
		ft_putstr_fd(str, 1);
	if (arg)
		ft_putstr_fd(arg, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}

int	failed_path(t_vars *vars, char *path)
{
	char	*pwd;

	errormsg("getcwd: Failed to access parent directory", "");
	pwd = get_env_value("PWD", vars->env);
	path = ft_strjoin("/", path);
	if (!path)
		clean_exit(vars, NULL, NULL, errno);
	add_to_ptrlst((void *)path, vars);
	path = ft_strjoin(pwd, path);
	if (!path)
		clean_exit(vars, NULL, NULL, errno);
	add_to_ptrlst((void *)path, vars);
	vars->env = set_env_value(vars->env, "PWD", path);
	if (!vars->env)
		clean_exit(vars, NULL, NULL, errno);
	return (0);
}
