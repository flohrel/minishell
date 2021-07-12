/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:47:20 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/12 11:50:19 by flohrel          ###   ########.fr       */
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

static int	check_error(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (errormsg("cd : aucun fichier ou dossier de ce type : ",
				path));
	else
	{
		close(fd);
		return (errormsg("cd : n'est pas un dossier : ", path));
	}
	return (1);
}

int	handle_args(t_vars *vars, char **args, char **path)
{
	if (ft_tablen(args) == 0 || ft_strcmp(args[0], "~") == 0)
	{
		*path = (get_env_value("HOME", vars->env));
		if (!*path)
		{
			errormsg("bash: cd: << HOME >> non défini", "");
			return (-1);
		}
	}
	else if (ft_strcmp(args[0], "-") == 0)
	{
		*path = get_env_value("OLDPWD", vars->env);
		if (!*path)
		{
			errormsg("bash: cd: << OLDPWD >> non défini", "");
			return (-1);
		}
	}
	else
		*path = args[0];
	return (1);
}

int	cd(char **args, t_vars *vars)
{
	char		s[255];
	const char	*path;

	if (ft_tablen(args) > 1)
		return (errormsg("cd : too many arguments", NULL));
	if (handle_args(vars, args, (char **)&path) < 0)
		return (1);
	if (chdir(path) < 0)
		return (check_error((char *)path));
	vars->env = set_env_value(vars->env, "OLDPWD",
			get_env_value("PWD", vars->env));
	if (!vars->env)
		clean_exit(vars, NULL, errno);
	vars->exp = set_env_value(vars->exp, "OLDPWD",
			get_env_value("PWD", vars->exp));
	if (!vars->exp)
		clean_exit(vars, NULL, errno);
	getcwd(s, 255);
	vars->env = set_env_value(vars->env, "PWD", ft_strdup(s));
	if (!vars->env)
		clean_exit(vars, NULL, errno);
	return (0);
}
