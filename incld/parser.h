/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:59:00 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/27 08:09:35 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdbool.h>
# include "data.h"
# include "lexer.h"
# include "utils.h"
# include "test.h"

# define BUFFER_SIZE	4096

/*
 **		parser.c
 */
int		parser(t_vars *vars, t_lexer *lexer, t_parser *parser);
int		astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser);

/*
 **		parser2.c
 */
int		is_charset(const char *charset, char c);
void	var_expansion(char *buffer, int *index, char **data);
int		parse_word(t_vars *vars, t_lexer *lexer, char **data);
int		parse_word2(t_vars *vars, char **data, char *buffer);
void	delete_empty_token(t_lexer *lexer, t_parser *parser);

/*
 **		parser3.c
 */
t_ast	*cmdline(t_vars *vars, t_parser *parser);
t_ast	*cmdline1(t_vars *vars, t_parser *parser);
t_ast	*cmdline2(t_vars *vars, t_parser *parser);
int		check_token(t_parser *parser, int type);

/*
 **		parser4.c
 */
t_ast	*job(t_vars *vars, t_parser *parser);
t_ast	*pipeline(t_vars *vars, t_parser *parser);

/*
 **		parser5.c
 */
t_ast	*cmd(t_vars *vars, t_parser *parser);
void	argument(t_vars *vars, t_token *token, t_cmd *data);
int		redirection(t_vars *vars, t_parser *parser, int type, t_cmd *data);
void	init_cmd_data(t_cmd *data);

#endif
