/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/22 15:56:26 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	display_prompt(void)
{
	write(1, PROMPT, ft_strlen(PROMPT));
}

void	ft_readline(t_vars *vars)
{
	char	buffer[BUFFER_SIZE];
	int		size;
	int		ret;

	size = -1;
	while (((ret = read(0, &buffer[++size], 1)) > 0) && (size < BUFFER_SIZE))
	{
		if (buffer[size] == '\n')
		{
			buffer[size] = 0;
			break ;
		}
	}
	if ((ret < 0) || (size == BUFFER_SIZE))
		clean_exit(vars, errno);
	vars->lexer.buffer = ft_calloc(size + 1, sizeof(*(vars->lexer.buffer)));
	if (vars->lexer.buffer == NULL)
		clean_exit(vars, errno);
	ft_strlcpy(vars->lexer.buffer, buffer, size + 1);
}
