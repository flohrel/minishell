/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/29 00:51:47 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	display_prompt(void)
{
	write(1, PROMPT, ft_strlen(PROMPT));
}

int		input_handle(char *input, int size, int *index)
{
//	printf("size = %d char=%d\n", size, *input);
	if (size == 1)
	{
		if (*input == '\n')
			return (0);
		else if (*input == 127)
		{
			if (*index)
				write(1, "\033[3D\033[0K", 8);
			else
				write(1, "\033[2D\033[0K", 8);
			return (-1);
		}
	}
	return (1);
}

void	ft_readline(t_vars *vars)
{
	char	buffer[BUFFER_SIZE];
	int		size;
	int		ret;
	int		i;

	size = 0;
	i = 0;
	ret = -1;
	while (ret)
	{
		size = read(0, &buffer[i], 4);
		if (size < 1)
		{
			if (!size)
				write(1, "exit\n", 5);
			clean_exit(vars, errno);
		}
		ret = input_handle(&buffer[i], size, &i);
		if (ret > 0)
			i += size;
	}
	vars->lexer.buffer = ft_calloc(i + 1, sizeof(*(vars->lexer.buffer)));
	if (vars->lexer.buffer == NULL)
		clean_exit(vars, errno);
	ft_strlcpy(vars->lexer.buffer, buffer, i + 1);
}
