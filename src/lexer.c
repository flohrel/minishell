/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:20:52 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/16 18:10:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

int		get_token_type(char c)
{
	if (c == '|')
		return (TK_PIPE);
	else if (c == ';')
		return (TK_SEMCOL);
	else if (c == '\'')
		return (TK_QUOTE);
	else if (c == '\"')
		return (TK_DQUOTE);
	else if (c == '\\')
		return (TK_ESCAPE);
	else if (c == '>')
		return (TK_GREATER);
	else if (c == '<')
		return (TK_LESSER);
	else if (c == ' ')
		return (TK_SPACE);
	else
		return (TK_STR);
}

void	lexer_init(t_vars *vars, void(*tk_handle[NTOKTYPE])(int))
{
	t_lexer	*input;

	input = &vars->input;
	input->buf_len = ft_strlen(input->buffer);
	input->ntoken = 0;
	input->token_list = ft_calloc(1, sizeof(*(input->token_list)));
	if (input->token_list == NULL)
		clean_exit(vars, 1);
	tk_handle[0] = 
}

int		lexer(t_vars *vars)
{
	int	i;
//	int	state;
	int	tk_type;
	(void)(*tk_handle[NTOKTYPE])(int);

	lexer_init(vars, tk_handle);
	i = -1;
	while (vars->input.buffer[++i])
	{
		tk_type = get_token_type(vars->input.buffer[i]);
		printf("%d\n", tk_type);
	}

	return (0);
}
