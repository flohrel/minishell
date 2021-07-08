/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/08 15:09:33 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_readline(t_vars *vars)
{
	char	*line_read;
	int	len;

	if (isatty(0))
		line_read = readline(PROMPT);
	else
		line_read = readline(NULL);
	if (line_read == NULL)
	{
		if (isatty(0))
			write(1, "exit\n", 5);
		else
			errno = 0;
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

int	input_handle(char *line_read, char *delim, char *buffer, int *index)
{
	int	ret;
	int	len;
	char	*ptr;

	ret = 1;
	len = ft_strlen(line_read);
	ptr = ft_strnstr(line_read, delim, len);
	if ((ptr != NULL) && (ptr != delim))
	{
		len = ptr - line_read + 1;
		ret = 0;
	}
	ft_strlcpy(&buffer[*index], line_read, len + 1);
	(*index) += len - 1;
	return (ret);
}

void	readline_hdoc(t_vars *vars, char *delim)
{
	char	buffer[BUFFER_SIZE];
	char	*line_read;
	int	ret;
	int	i;

	i = 0;
	ret = 1;
	while (ret)
	{
		if (isatty(0))
			line_read = readline(HDOC_PROMPT);
		else
			line_read = readline(NULL);
		ret = input_handle(line_read, delim, buffer, &i);
	}
	vars->lexer.buffer = lst_alloc(i + 1, sizeof(*buffer), vars);
	ft_strlcpy(vars->lexer.buffer, buffer, i + 1);
}
