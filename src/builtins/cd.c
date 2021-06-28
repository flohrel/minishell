/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:47:20 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/24 19:54:25 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	cd(char **args, t_vars *vars)
{
	char		s[255];
	const char	*path;

	if (ft_tablen(args) > 1)
		return (errormsg("cd : too many arguments", NULL));
	if (ft_tablen(args) == 0)
	{
		write(1, "ii", sizeof(char *));
		path = (get_env_value("HOME", vars->env));
	}
	else
		path = args[0];
	if (chdir(path) < 0)
		return (check_error((char *)path));
	vars->env = set_env_value(vars->env, "OLDPWD",
			get_env_value("PWD", vars->env));
	getcwd(s, 255);
	vars->env = set_env_value(vars->env, "PWD", ft_strdup(s));
	return (1);
}
