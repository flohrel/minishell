/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:49:41 by mtogbe            #+#    #+#             */
/*   Updated: 2021/05/31 17:26:13 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_echo(char **args, t_vars *vars)
{
	int	i;
	int	j;
	int	opt;

	(void)vars;
	opt = 0;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			write(1, &(args[i][j++]), 1);
		write(1, " ", 1);
		i++;
	}
	if (opt)
		write(1, "\n", 1);
	return (1);
}
