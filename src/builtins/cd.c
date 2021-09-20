/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:47:20 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/09 17:12:04 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*add_cdpath(t_vars *vars, char *path)
{
	char	*cdpath;
	char	*new_path;
	char	s[255];

	if (!ft_strcmp(path, ".") || !ft_strcmp(path, ".."))
		return (path);
	cdpath = get_env_value("CDPATH", vars->env);
	if (!cdpath)
		return (path);
	new_path = ft_strjoin(cdpath, path);
	if (!new_path)
		clean_exit(vars, NULL, NULL, errno);
	add_to_ptrlst((void *)new_path, vars);
	if (chdir(new_path) == 0 && getcwd(s, 255))
		printf("%s\n", s);
	return (path);
}

static int	check_error(char *path)
{
	int	fd;

	if (ft_strlen(path) < 1)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (errormsg("cd : no such file or directory : ",
				path));
	else
	{
		close(fd);
		return (errormsg("cd : is not a folder : ", path));
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
			errormsg("minishell: cd: << HOME >> not defined",
				"");
			return (-1);
		}
	}
	else if (ft_strcmp(args[0], "-") == 0)
	{
		*path = get_env_value("OLDPWD", vars->env);
		if (!*path)
		{
			errormsg("minishell: cd: << OLDPWD >> not defined",
				"");
			return (-1);
		}
		ft_putendl_fd(*path, 1);
	}
	else
		*path = add_cdpath(vars, args[0]);
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
	if ((getcwd(s, 255) || chdir(path) < 0)
		&& getcwd(s, 255) && ft_strcmp(get_env_value("PWD", vars->env), s) == 0
		&& chdir(path) < 0)
		return (check_error((char *)path));
	vars->env = set_env_value(vars->env, "OLDPWD",
			get_env_value("PWD", vars->env));
	if (!vars->env)
		clean_exit(vars, NULL, NULL, errno);
	vars->exp = set_env_value(vars->exp, "OLDPWD",
			get_env_value("PWD", vars->exp));
	if (!vars->exp)
		clean_exit(vars, NULL, NULL, errno);
	if (!getcwd(s, 255))
		return (failed_path(vars, (char *)path));
	vars->env = set_env_value(vars->env, "PWD", s);
	if (!vars->env)
		clean_exit(vars, NULL, NULL, errno);
	return (0);
}
