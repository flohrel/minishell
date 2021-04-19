#include "exit.h"

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->data)
		free(token->data);
}

void	clean_exit(t_vars *vars, int status)
{
	ft_lstclear(&vars->lexer.tokens, del_token);
	free(vars->lexer.buffer);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
