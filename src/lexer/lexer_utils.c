/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:58:34 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/13 17:55:10 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	get_token_char(int type)
{
	if (check_flag(type, TK_PIPE))
		return ('|');
	else if (check_flag(type, TK_AMP))
		return ('&');
	else if (check_flag(type, TK_QUOTE))
		return ('\'');
	else if (check_flag(type, TK_DQUOTE))
		return ('\"');
	else if (check_flag(type, TK_GREAT))
		return ('>');
	else if (check_flag(type, TK_LESS))
		return ('<');
	else if (check_flag(type, TK_SPACE))
		return (' ');
	else if (check_flag(type, TK_OPPAR))
		return ('(');
	else if (check_flag(type, TK_CLPAR))
		return (')');
	else
		return (0);
}

int	get_token_type(char c)
{
	if (c == '|')
		return (TK_PIPE);
	else if (c == '&')
		return (TK_AMP);
	else if (c == '\'')
		return (TK_QUOTE | TK_ESC);
	else if (c == '\"')
		return (TK_DQUOTE | TK_ESC);
	else if (c == '>')
		return (TK_GREAT | TK_REDIR);
	else if (c == '<')
		return (TK_LESS | TK_REDIR);
	else if (c == ' ')
		return (TK_SPACE);
	else if (c == '(')
		return (TK_OPPAR | TK_COMPND);
	else if (c == ')')
		return (TK_CLPAR | TK_COMPND);
	else
		return (TK_WORD);
}

void	new_token(t_vars *vars, int type, int size)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*lst;

	lexer = &vars->lexer;
	token = lst_alloc(1, sizeof(*token), vars);
	token->type = type;
	token->data = NULL;
	lexer->cur_char = NULL;
	if (size)
	{
		token->data = lst_alloc(size + 1, sizeof(char), vars);
		lexer->cur_char = token->data;
	}
	lst = lst_alloc(1, sizeof(*lst), vars);
	lst->content = token;
	lst->next = NULL;
	ft_lstadd_back(&lexer->tk_list, lst);
}

void	delete_empty_token(t_lexer *lexer, t_parser *parser)
{
	if (parser->prev_tk == NULL)
	{
		lexer->tk_list = lexer->tk_list->next;
		parser->cur_tk = lexer->tk_list;
	}
	else
	{
		parser->prev_tk->next = parser->cur_tk->next;
		parser->cur_tk = parser->prev_tk->next;
	}
}

int	syntax_error(t_token *token)
{
	ft_putstr_fd("bash: syntax error", STDERR_FILENO);
	if (token == NULL)
	{
		ft_putstr_fd(": quote missing\n", STDERR_FILENO);
		return (-1);
	}
	ft_putstr_fd(" near unexpected token `", STDERR_FILENO);
	if (token->type == TK_NL)
		ft_putstr_fd("newline", STDERR_FILENO);
	else if (check_flag(token->type, TK_DGREAT))
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (check_flag(token->type, TK_DLESS | TK_DLESS2))
		ft_putstr_fd("<<", STDERR_FILENO);
	else if (check_flag(token->type, TK_DAMP))
		ft_putstr_fd("&&", STDERR_FILENO);
	else if (check_flag(token->type, TK_DPIPE))
		ft_putstr_fd("||", STDERR_FILENO);
	else
		ft_putchar_fd(get_token_char(token->type), STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	g_sig.exit_status = 2;
	return (-1);
}
