#include "exit.h"

void	clean_exit(t_vars *vars, int status)
{
	t_token	*token;

	token = vars->input.token_list;
	while (token != NULL)
	{
		vars->input.token_list = token->next;
		free(token);
		token = vars->input.token_list;
	}
	free(vars->input.buffer);
	exit(status);
}
