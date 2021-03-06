/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/30 17:04:22 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	ft_readline(t_vars *vars)
{
	char	*line_read;
	int		len;

	line_read = display_prompt();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (line_read == NULL)
	{
		if (isatty(0))
			write(1, "exit", 5);
		clean_exit(vars, NULL, NULL, -127);
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
	int		ret;
	int		len;

	ret = 1;
	len = ft_strlen(line_read);
	if (!ft_strcmp(line_read, delim))
		ret = 0;
	else
	{
		ft_strlcpy(&buffer[*index], line_read, len + 1);
		(*index) += len;
		buffer[*index] = '\n';
		(*index)++;
	}
	buffer[*index] = '\0';
	free(line_read);
	return (ret);
}

int	get_nline(t_vars *vars)
{
	int		fd;
	int		ret;
	int		nline;
	char	*line;

	fd = open(HDOC_DATA, O_RDONLY | O_CREAT, 0600);
	if (fd == -1)
		clean_exit(vars, NULL, NULL, errno);
	line = NULL;
	ret = get_next_line(fd, &line);
	if (ret == -1)
		nline = 1;
	else
	{
		nline = ft_atoi(line);
		free(line);
	}
	close(fd);
	return (nline);
}

void	set_nline(t_vars *vars, int count)
{
	int		fd;
	int		ret;
	char	*nline;
	char	*line;

	fd = open(HDOC_DATA, O_RDONLY | O_CREAT, 0600);
	if (fd == -1)
		clean_exit(vars, NULL, NULL, errno);
	line = NULL;
	ret = get_next_line(fd, &line);
	if (ret == -1)
		nline = ft_itoa(count);
	else
	{
		nline = ft_itoa(ft_atoi(line) + count);
		free(line);
	}
	close(fd);
	fd = open(HDOC_DATA, O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		clean_exit(vars, NULL, NULL, errno);
	write(fd, nline, ft_strlen(nline));
	close(fd);
	free(nline);
}

void	readline_hdoc(t_vars *vars, char *delim)
{
	char		buffer[BUFFER_SIZE];
	char		*line_read;
	int			count;
	int			ret;
	int			i;

	i = 0;
	ret = 1;
	count = 0;
	ft_bzero(buffer, BUFFER_SIZE);
	while (ret)
	{
		count++;
		line_read = readline(HDOC_PROMPT);
		if (line_read == NULL)
			ret = heredoc_error_msg(vars, delim, line_read);
		else
			ret = input_handle(line_read, delim, buffer, &i);
	}
	set_nline(vars, count);
	vars->lexer.buffer = lst_alloc(i + 1, sizeof(*buffer), vars);
	ft_strlcpy(vars->lexer.buffer, buffer, i + 1);
}
