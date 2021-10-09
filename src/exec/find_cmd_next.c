/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 03:42:43 by mtogbe            #+#    #+#             */
/*   Updated: 2021/08/06 16:17:58 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

void	exec_absolute_path(char *path, char **argv, char **envp, t_vars *vars)
{
	int			fd;
	struct stat	buf;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_exit(vars, path, NULL, errno);
	close(fd);
	if (execve(path, argv, envp) < 0)
	{
		if (stat(path, &buf))
			clean_exit(vars, path, NULL, errno);
		if (S_ISDIR(buf.st_mode))
			path_error(path, ": is a directory.\n");
		else if (buf.st_mode & S_IXUSR)
		{
			path_error(path, ": command not found.\n");
			exit(127);
		}
		else
			path_error(path, ": Permission denied.\n");
		exit(126);
	}
}
