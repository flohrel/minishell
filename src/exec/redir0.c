/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 01:07:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/19 19:39:22 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	set_rdout(t_io *io, char *pathname)
{
	set_flag(&io->flag, RD_OUT);
	if (!(*pathname) || ft_strchr(pathname, ' '))
		return (redir_error(NULL));
	io->redir[FD_OUT] = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->redir[FD_OUT] == -1)
		return (redir_error(pathname));
	return (0);
}

int	set_rdapp(t_io *io, char *pathname)
{
	set_flag(&io->flag, RD_OUT);
	if (!(*pathname) || ft_strchr(pathname, ' '))
		return (redir_error(NULL));
	io->redir[FD_OUT] = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->redir[FD_OUT] == -1)
		return (redir_error(pathname));
	return (0);
}

int	set_rdin(t_io *io, char *pathname)
{
	set_flag(&io->flag, RD_IN);
	if (!(*pathname) || ft_strchr(pathname, ' '))
		return (redir_error(NULL));
	io->redir[FD_IN] = open(pathname, O_RDONLY);
	if (io->redir[FD_IN] == -1)
		return (redir_error(pathname));
	return (0);
}

int	set_hdoc(t_vars *vars, t_io *io, char *string, bool has_exp)
{
	char	*buf;
	char	buffer[BUFFER_SIZE];

	set_flag(&io->flag, RD_IN);
	io->redir[FD_IN] = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (io->redir[FD_IN] == -1)
		return (redir_error(TMP_FILE));
	readline_hdoc(vars, string);
	buf = buffer;
	hdoc_copy(vars, &buf, vars->lexer.buffer, has_exp);
	write(io->redir[FD_IN], buffer, buf - buffer);
	close(io->redir[FD_IN]);
	io->redir[FD_IN] = open(TMP_FILE, O_RDONLY);
	if (io->redir[FD_IN] == -1)
		return (redir_error(TMP_FILE));
	return (0);
}

int	parse_redir(t_vars *vars, t_param *param)
{
	t_list	*lst;

	lst = param->redir;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (parse_redir2(vars, param, lst->content) == -1)
			return (-1);
		lst = lst->next;
	}
	return (0);
}
