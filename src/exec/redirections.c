#include <minishell.h>

void	set_rdout(t_cmd *cmd)
{
	set_flag(&cmd->io_bit, RD_OUT);
	clear_flag(&cmd->io_bit, RD_APP);
	cmd->redir[FD_OUT] = open(
}

void	set_rdapp(t_cmd *cmd)
{
	set_flag(&cmd->io_bit, RD_OUT | RD_APP);
}

void	set_rdin(t_cmd *cmd)
{
	set_flag(&cmd->io_bit, RD_IN);
	clear_flag(&cmd->io_bit, RD_HDOC);
}

void	set_hdoc(t_cmd *cmd)
{
	set_flag(&cmd->io_bit, RD_IN | RD_HDOC);
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
			set_rdout(&vars->cmd, token->data);
		else if (token->type == TK_DLESS)
			set_rdapp(&vars->cmd, token->data);
		else if (token->type == TK_GREAT)
			set_rdin(&vars->cmd, token->data);
		else
			set_hdoc(&vars->cmd, token->data);
		lst = lst->next;
	}
}
