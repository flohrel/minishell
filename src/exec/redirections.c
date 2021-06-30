/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 01:07:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/30 02:05:03 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

void	set_rdout(t_vars *vars, t_cmd *cmd, char *pathname)
{
	set_flag(&cmd->io_bit, RD_OUT);
	clear_flag(&cmd->io_bit, RD_APP);
	cmd->redir[FD_OUT] = open(pathname, O_WRONLY | O_CREAT | O_TRUNC
			| S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (cmd->redir[FD_OUT] == -1)
		clean_exit(vars, errno);
}

void	set_rdapp(t_vars *vars, t_cmd *cmd, char *pathname)
{
	set_flag(&cmd->io_bit, RD_OUT | RD_APP);
	cmd->redir[FD_OUT] = open(pathname, O_WRONLY | O_CREAT | O_APPEND);
	if (cmd->redir[FD_OUT] == -1)
		clean_exit(vars, errno);
}

void	set_rdin(t_vars *vars, t_cmd *cmd, char *pathname)
{
	set_flag(&cmd->io_bit, RD_IN);
	clear_flag(&cmd->io_bit, RD_HDOC);
	cmd->redir[FD_IN] = open(pathname, O_RDONLY);
	if (cmd->redir[FD_IN] == -1)
		clean_exit(vars, errno);
}

void	set_hdoc(t_vars *vars, t_cmd *cmd, char *string)
{
	(void)string;
	set_flag(&cmd->io_bit, RD_IN | RD_HDOC);
	cmd->redir[FD_IN] = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC
			| S_IRUSR | S_IWUSR);
	if (cmd->redir[FD_IN] == -1)
		clean_exit(vars, errno);
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
		if (token->type == TK_LESS)
			set_rdout(vars, &vars->cmd, token->data);
		else if (token->type == TK_DLESS)
			set_rdapp(vars, &vars->cmd, token->data);
		else if (token->type == TK_GREAT)
			set_rdin(vars, &vars->cmd, token->data);
//		else
//			set_hdoc(vars, &vars->cmd, token->data);
		lst = lst->next;
	}
}
