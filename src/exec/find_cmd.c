/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:52:04 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/11 16:43:28 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

char	*create_path(char *path, char *cmd, t_vars *vars)
{
	char	*result;

	result = ft_strjoin(path, "/");
	if (!result || !(add_to_ptrlst((void *)result, vars)))
		return (NULL);
	result = ft_strjoin(result, cmd);
	if (!result || !(add_to_ptrlst((void *)result, vars)))
		return (NULL);
	return (result);
}

int	exec_cmd(char *path, char **argv, char **envp, t_vars *vars)
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
		path_x = create_path(paths[i], path, vars);
		if (!path_x)
			return (-1);
		if (execve(path_x, argv, envp) < 0)
			i++;
		else
			return (1);
	}
	return (1);
}

int	find_cmd(char *path, char **argv, char **envp, t_vars *vars)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		exec_cmd(path, tabjoin(path, argv, vars), envp, vars);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (1);
}
