/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:47:20 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/02 19:57:45 by mtogbe           ###   ########.fr       */
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

int	cd(char **args, t_vars *vars)
{
	char		s[255];
	const char	*path;
	DIR			*dir;

	if (ft_tablen(args) > 1)
		return (errormsg("cd : too many arguments", NULL));
	if (ft_tablen(args) == 0)
		path = (get_env_value("HOME", vars->env));
	else
	{
		dir = opendir(args[0]);
		if (!dir)
			return (errormsg("cd : n'est pas un dossier : ",
						args[0]));
		closedir(dir);
		path = args[0];
	}
	if (chdir(path) < 0)
		return (errormsg("cd : aucun fichier ou dossier de ce type : ",
					(char *)path));
	vars->env = set_env_value(vars->env, "OLDPWD",
			get_env_value("PWD", vars->env));
	getcwd(s, 255);
	vars->env = set_env_value(vars->env, "PWD", ft_strdup(s));
	return (1);
}
