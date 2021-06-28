#include <minishell.h>

int	handle_redirections(t_param *param)
{
	t_token	*tk_redir;

	while (param->redir)
	{
		tk_redir = (t_token *)(param->redir->content);
		if (tk_redir->type == TK_GREAT)
			write(1, "o", 1);
		param->redir = param->redir->next;
	}
	return (1);
}
