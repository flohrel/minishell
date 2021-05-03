/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:58:34 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/03 17:10:07 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		get_token_type(char c)
{
	if (c == '|')
		return (TK_PIPE);
	else if (c == ';')
		return (TK_SEMI);
	else if (c == '\'')
		return (TK_QUOTE);
	else if (c == '\"')
		return (TK_DQUOTE);
	else if (c == '\\')
		return (TK_ESC);
	else if (c == '>')
		return (TK_GREAT);
	else if (c == '<')
		return (TK_LESS);
	else if (c == ' ')
		return (TK_SPACE);
	else
		return (TK_CHAR);
}

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token && token->data)
		free(token->data);
}

void	new_token(t_vars *vars, int type, int size)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*lst;

	lexer = &vars->lexer;
	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		clean_exit(vars, errno);
	token->type = type;
	token->data = NULL;
	lexer->cur_char = NULL;
	if (size)
	{
		token->data = ft_calloc(size + 1, sizeof(char));
		if (token->data == NULL)
			clean_exit(vars, errno);
		lexer->cur_char = token->data;
	}
	lst = ft_lstnew(token);
	if (lst == NULL)
		clean_exit(vars, errno);
	ft_lstadd_back(&lexer->tokens, lst);
}
