/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:52:04 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/03 17:48:51 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

char	*create_path(char *path, char *cmd)
{
	char	*result;

	result = ft_strjoin(path, "/");
	if (!result)
		return (NULL);
	result = ft_strjoin(result, cmd);
	if (!result)
		return (NULL);
	return (result);
}

int	find_cmd(char *path, char **argv, char **envp, t_vars *vars)
{
//	DIR				*dir;
//	struct dirent	*s_dir;
	char		**paths;
	int		i;
	char		*path_x;

	i = 0;
	if (ft_ischarset('/', path))
	{
		if (execve(path, argv, envp) < 0)
			printf("bash : %s: No such file or directory.", path);
		ft_putstr_fd("executing\n", 1);
	}
	/*else
	{
		dir = opendir("/bin/");
		do
		{
			s_dir = readdir(dir);
			if (s_dir && !(strcmp(s_dir->d_name, path)))
			{
				printf("exec %s\n", s_dir->d_name);
			}
		} while (s_dir);
		closedir(dir);
	}*/
	// ou directment faire un execve avec le path "/bin/" + pathname
	paths = ft_split(get_env_value("PATH", vars->env), ':');
	if (!paths)
		return (-1);
	while (paths[i])
	{
		path_x = create_path(paths[i], path);
		if (!path_x)
			return (-1);
		if (execve(path_x, argv, envp) < 0)
			i++;
		else
			return (1);
	}
	return (1);
}
