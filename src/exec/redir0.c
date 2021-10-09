/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 01:07:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/01 18:20:12 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_rdout(t_vars *vars, t_io *io, char *pathname)
{
	set_flag(&io->flag, RD_OUT);
	if (!pathname || ft_strchr(pathname, ' '))
		clean_exit(vars, NULL, "ambiguous redirect", -126);
	io->redir[FD_OUT] = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->redir[FD_OUT] == -1)
		clean_exit(vars, pathname, NULL, errno);
}

void	set_rdapp(t_vars *vars, t_io *io, char *pathname)
{
	set_flag(&io->flag, RD_OUT);
	if (!pathname || ft_strchr(pathname, ' '))
		clean_exit(vars, NULL, "ambiguous redirect", -126);
	io->redir[FD_OUT] = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->redir[FD_OUT] == -1)
		clean_exit(vars, pathname, NULL, errno);
}

void	set_rdin(t_vars *vars, t_io *io, char *pathname)
{
	set_flag(&io->flag, RD_IN);
	if (!pathname)
		clean_exit(vars, NULL, "ambiguous redirect", -126);
	io->redir[FD_IN] = open(pathname, O_RDONLY);
	if (io->redir[FD_IN] == -1)
		clean_exit(vars, pathname, NULL, errno);
}

void	set_hdoc(t_vars *vars, t_io *io, char *string, bool has_exp)
{
	char	*str;
	char	*buf;
	char	buffer[BUFFER_SIZE];

	set_flag(&io->flag, RD_IN);
	io->redir[FD_IN] = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (io->redir[FD_IN] == -1)
		clean_exit(vars, TMP_FILE, NULL, errno);
	readline_hdoc(vars, string);
	str = vars->lexer.buffer;
	buf = buffer;
	while (*str)
	{
		if ((*str == '$') && (has_exp == true))
			var_expansion(vars, &buf, &str);
		else
			*buf = *str;
		buf++;
		str++;
	}
	write(io->redir[FD_IN], buffer, buf - buffer);
	close(io->redir[FD_IN]);
	io->redir[FD_IN] = open(TMP_FILE, O_RDONLY);
	if (io->redir[FD_IN] == -1)
		clean_exit(vars, TMP_FILE, NULL, errno);
}

void	parse_redir(t_vars *vars, t_param *param)
{
	t_list	*lst;
	t_token	*token;

	lst = param->redir;
	if (lst == NULL)
		return ;
	while (lst)
	{
		token = (t_token *)lst->content;
		close_redir(&param->io);
		if (check_flag(token->type, TK_GREAT))
			set_rdout(vars, &param->io, token->data);
		else if (check_flag(token->type, TK_DGREAT))
			set_rdapp(vars, &param->io, token->data);
		else if (check_flag(token->type, TK_LESS))
			set_rdin(vars, &param->io, token->data);
		else
		{
			if (check_flag(token->type, TK_DLESS2))
				set_hdoc(vars, &param->io, token->data, false);
			else
				set_hdoc(vars, &param->io, token->data, true);
		}
		lst = lst->next;
	}
}
