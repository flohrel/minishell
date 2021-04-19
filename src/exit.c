#include "exit.h"

void	clean_exit(t_vars *vars, int status)
{
	t_token	*token;

	token = vars->lexer.token_list;
	while (token != NULL)
	{
		vars->lexer.token_list = token->next;
		free(token);
		token = vars->lexer.token_list;
	}
	free(vars->lexer.buffer);
	exit(status);
}
