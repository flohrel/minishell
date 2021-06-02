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
	t_opt	options;
	
	i = 0;
	options = optionhandler(args, "n", vars);
	while (options.args[i])
	{
		j = 0;
		while (options.args[i][j])
			write(1, &(options.args[i][j++]), 1);
		i++;
		if (options.args[i])
			write(1, " ", 1);
	}
	if (!(options.optflag[0]))
		write(1, "\n", 1);
	return (1);
}
