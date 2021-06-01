/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:52:04 by mtogbe            #+#    #+#             */
/*   Updated: 2021/05/28 17:16:26 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

int	ft_ischarset(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	find_cmd(char *path, char **argv, char **envp)
{
	DIR				*dir;
	struct dirent	*s_dir;

	if (ft_ischarset(path, '/'))
	{
		if (execve(path, argv, envp) < 0)
			printf("bash : %s: No such file or directory.");
	}
	else
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
	}
	// ou directment faire un execve avec le path "/bin/" + pathname
	closedir(dir);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	find_cmd(av[1], av + 1, envp);
}
