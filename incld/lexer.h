/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:29 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/07 16:11:57 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "data.h"
# include "utils.h"
# include "libft.h"
# include "stdlib.h"

/*
 **		lexer0.c
 */
int		lexer(t_vars *vars, t_lexer *lexer);
void	lexer_init(t_vars *vars);
void	quote_handle(t_vars *vars, char *buf);
void	token_handle(t_vars *vars, int tk_type, char **buffer);

/*
 **		lexer1.c
 */
void	redirection_handle(t_vars *vars, int tk_type, char **buf);
void	job_handle(t_vars *vars, int tk_type, char **buf);
void	word_handle(t_vars *vars, int tk_type, char **buf);
void	space_handle(t_vars *vars, int tk_type, char **buf);
void	compound_handle(t_vars *vars, int tk_type, char **buf);

/*
 **		lexer_utils.c
 */
char	get_token_char(int type);
int		get_token_type(char c);
void	new_token(t_vars *vars, int type, int size);
void	delete_empty_token(t_lexer *lexer, t_parser *parser);
int		syntax_error(t_token *token);

#endif
