/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/07 22:49:37 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	var_expansion(char *buffer, int *index, char **data)
{
	char	*var;
	int		size;

	var = ft_strtok_r(*data + 1, " \"", data);
	var = getenv(var);
	size = ft_strlen(var);
	ft_strlcpy(&buffer[*index], var, size + 1);
	(*index) += size;
}

void	parse_word(t_vars *vars, t_lexer *lexer, char *data)
{
	char	buffer[BUFFER_SIZE];
	int		index;

	(void)vars;
	index = 0;
	while (*data)
	{
		if (*data == '\'')
		{
			if (lexer->state == ST_GENERAL)
				lexer->state = ST_QUOTE;
			else
				lexer->state = ST_GENERAL;
		}
		else if ((*data == '$') && (lexer->state != ST_QUOTE))
		{
			var_expansion(buffer, &index, &data);
			continue ;
		}
		buffer[index++] = *data++;
	}
	printf("%s", buffer);
}

void	delete_empty_token(t_lexer *lexer, t_parser *parser)
{
	if (parser->prev_tk == NULL)
	{
		lexer->tk_list = lexer->tk_list->next;
		ft_lstdelone(parser->cur_tk, del_token);
		parser->cur_tk = lexer->tk_list;
	}
	else
	{
		parser->prev_tk->next = parser->cur_tk->next;
		ft_lstdelone(parser->cur_tk, del_token);
		parser->cur_tk = parser->prev_tk->next;
	}
}

int		syntax_error(char *token)
{
	ft_putstr_fd("bash: syntax error", STDERR_FILENO);
	if (token == NULL)
		ft_putstr_fd(": quote missing", STDERR_FILENO);
	else
	{
		ft_putstr_fd("near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	return (-1);
}

int		parser(t_vars *vars, t_lexer *lexer, t_parser *parser)
{
	t_token		*token;

	parser->cur_tk = lexer->tk_list;
	parser->prev_tk = NULL;
	if (lexer->state != ST_GENERAL)
		return (syntax_error(NULL));
	while (parser->cur_tk)
	{
		token = (t_token *)parser->cur_tk->content;
		if ((token->type < 0) && (!token->data || !(*token->data)))
			delete_empty_token(lexer, parser);
		else
		{
			if (token->type < 0)
				parse_word(vars, lexer, token->data);
			parser->prev_tk = parser->cur_tk;
			parser->cur_tk = parser->prev_tk->next;
		}
	}
	return (0);
}
