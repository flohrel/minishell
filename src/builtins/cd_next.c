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
		ft_putstr_fd(str, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
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

int	check_pwd(const char *path, t_vars *vars)
{
	char		s[255];
	if ((getcwd(s, 255) || chdir(path) < 0)
		&& getcwd(s, 255)
		&& (!get_env_value("PWD", vars->env)
		|| ft_strcmp(get_env_value("PWD", vars->env), s) == 0)
		&& chdir(path) < 0)
		return (0);
	return (1);

}

int	cd_end(const char *path, t_vars *vars)
{
	char	s[255];

	vars->env = set_env_value(vars->env, "OLDPWD",
			get_env_value("PWD", vars->env));
	if (!vars->env)
		clean_exit(vars, NULL, NULL, errno);
	vars->exp = set_env_value(vars->exp, "OLDPWD",
			get_env_value("PWD", vars->env));
	if (!vars->exp)
		clean_exit(vars, NULL, NULL, errno);
	if (!getcwd(s, 255))
		return (failed_path(vars, (char *)path));
	if (get_env_value("PWD", vars->env))
	{
		vars->env = set_env_value(vars->env, "PWD", s);
		if (!vars->env)
			clean_exit(vars, NULL, NULL, errno);
		vars->exp = set_env_value(vars->exp, "PWD", s);
		if (!vars->exp)
			clean_exit(vars, NULL, NULL, errno);
	}
	return (0);
}

