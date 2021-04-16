/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:29 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/16 18:11:43 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
**		VARIABLES
*/

enum	e_toktype {
	CHAR = 0,
	PIPE = '|',
	SEMICOLON = ';',
	QUOTE = '\'',
	DQUOTE = '\"',
	SPACE = ' ',
	ESCAPE = '\\',
	GREATER = '>',
	LESSER = '<',
	DOLLAR = '$',
};

typedef struct		s_tok
{
	int				type;
	char			*data;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_lexer
{
	int		ntok;
	t_tok	*list;
}					t_lexer;

/*
**		FUNCTIONS
*/
int					lexer(char *input, t_lexer *lexbuf);

#endif
