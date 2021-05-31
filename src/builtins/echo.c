/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:49:41 by mtogbe            #+#    #+#             */
/*   Updated: 2021/05/29 17:56:58 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_echo(int fd, char **args, t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			write(fd, &(args[i][j++]), 1);
		write(fd, " ", 1);
		i++;
	}
	if (opt)
		write(fd, "\n", 1);
	return (1);
}
