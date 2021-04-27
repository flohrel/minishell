/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:29 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/28 00:59:10 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "exit.h"
# include "libft.h"
# include "stdlib.h"

/*
 **		lexer.c
 */
void	lexer(t_vars *vars);

/*
 **		lexer2.c
 */
void	job_token_handle(int tk_type, t_vars *vars, char **buf);
void	word_handle(t_vars *vars, char **buf);
void	space_handle(t_vars *vars, char **buf);
void	escape_handle(t_vars *vars, char **buf);
void	quote_handle(t_vars *vars, char *buf);

/*
 **		token.c
 */
int		get_token_type(char c);
void	new_token(t_vars *vars, int type, int size);
void	del_token(void *content);

#endif
