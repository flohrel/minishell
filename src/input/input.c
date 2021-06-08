/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/08 09:09:12 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_readline(t_vars *vars)
{
	char	*line_read;
	int		len;

	line_read = readline(PROMPT);
	if (line_read == NULL)
	{
		write(1, "exit\n", 5);
		clean_exit(vars, 0);
	}
	len = ft_strlen(line_read);
	vars->lexer.buffer = lst_alloc(len + 1,
			sizeof(*(vars->lexer.buffer)), vars);
	ft_strlcpy(vars->lexer.buffer, line_read, len + 1);
	if (line_read && *line_read)
		add_history(line_read);
	free(line_read);
}
