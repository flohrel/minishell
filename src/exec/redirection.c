/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 01:07:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/20 05:20:16 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	set_rdout(t_vars *vars, t_cmd *cmd, char *pathname)
{
	set_flag(&cmd->io_bit, RD_OUT);
	cmd->redir[FD_OUT] = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (cmd->redir[FD_OUT] == -1)
		clean_exit(vars, pathname, errno);
}

void	set_rdapp(t_vars *vars, t_cmd *cmd, char *pathname)
{
	set_flag(&cmd->io_bit, RD_OUT);
	cmd->redir[FD_OUT] = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (cmd->redir[FD_OUT] == -1)
		clean_exit(vars, pathname, errno);
}

void	set_rdin(t_vars *vars, t_cmd *cmd, char *pathname)
{
	set_flag(&cmd->io_bit, RD_IN);
	cmd->redir[FD_IN] = open(pathname, O_RDONLY);
	if (cmd->redir[FD_IN] == -1)
		clean_exit(vars, pathname, errno);
}

void	set_hdoc(t_vars *vars, t_cmd *cmd, char *string)
{
	char	*str;
	char	*buf;
	char	buffer[BUFFER_SIZE];

	set_flag(&cmd->io_bit, RD_IN);
	cmd->redir[FD_IN] = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (cmd->redir[FD_IN] == -1)
		clean_exit(vars, TMP_FILE, errno);
	readline_hdoc(vars, string);
	str = vars->lexer.buffer;
	buf = buffer;
	while (*str)
	{
		if (*str == '$')
			var_expansion(vars, &buf, &str);
		else
			*buf = *str;
		buf++;
		str++;
	}
	write(cmd->redir[FD_IN], buffer, buf - buffer);
	close(cmd->redir[FD_IN]);
	cmd->redir[FD_IN] = open(TMP_FILE, O_RDONLY);
	if (cmd->redir[FD_IN] == -1)
		clean_exit(vars, TMP_FILE, errno);
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
		if (token->type == TK_GREAT)
			set_rdout(vars, &vars->cmd, token->data);
		else if (token->type == TK_DGREAT)
			set_rdapp(vars, &vars->cmd, token->data);
		else if (token->type == TK_LESS)
			set_rdin(vars, &vars->cmd, token->data);
		else
			set_hdoc(vars, &vars->cmd, token->data);
		lst = lst->next;
	}
}