/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:59:00 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/10 01:02:37 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdbool.h>
# include "data.h"
# include "lexer.h"

# define BUFFER_SIZE	4096

/*
 **		parser.c
 */
int		parser(t_vars *vars, t_lexer *lexer, t_parser *parser);
int		syntax_error(char *token);

/*
 **		parser2.c
 */
int		is_charset(const char *charset, char c);
void	var_expansion(char *buffer, int *index, char **data);
int		parse_word(t_vars *vars, t_lexer *lexer, char **data);
int		parse_word2(t_vars *vars, char **data, char *buffer);
void	delete_empty_token(t_lexer *lexer, t_parser *parser);

/*
 **		astree.c
 */
t_ast	*astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser);

#endif
