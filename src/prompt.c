/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/19 12:21:47 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	ft_readline(t_vars *vars, const char *prompt)
{
	char	buffer[BUFFER_SIZE];
	int		size;
	int		ret;

	write(1, prompt, ft_strlen(prompt));
	size = -1;
	while ((ret = read(0, &buffer[++size], 1)) > 0)
	{
		if (buffer[size] == '\n')
		{
			buffer[size] = 0;
			break ;
		}
	}
	if (ret < 0)
		clean_exit(vars, errno);
	vars->lexer.buffer = ft_calloc(size + 1, sizeof(*(vars->lexer.buffer)));
	if (vars->lexer.buffer == NULL)
		clean_exit(vars, errno);
	ft_strlcpy(vars->lexer.buffer, buffer, size + 1);
	vars->lexer.buf_len = size;
}
