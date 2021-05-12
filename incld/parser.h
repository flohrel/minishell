/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:59:00 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/12 22:09:54 by flohrel          ###   ########.fr       */
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
 **		parser3.c
 */
int		astree_build(t_vars *vars, t_lexer *lexer, t_parser *parser);
t_ast	*cmdline(t_vars *vars, t_parser *parser);
t_ast	*cmdline1(t_vars *vars, t_parser *parser);
t_ast	*cmdline2(t_vars *vars, t_parser *parser);
int		check_token(t_parser *parser, int type);

/*
 **		parser3.c
 */
t_ast	*cmd(t_vars *vars, t_parser *parser);
t_ast	*job(t_vars *vars, t_parser *parser);
t_ast	*job1(t_vars *vars, t_parser *parser);

/*
 **		astree.c
 */
t_ast	*tree_new_node(t_vars *vars, int type, char *data);
void	tree_attach_branch(t_ast *root, t_ast *left, t_ast *right);
void	tree_delete_node(t_ast *node);

#endif
