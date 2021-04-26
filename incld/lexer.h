/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:29 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/25 05:14:04 by flohrel          ###   ########.fr       */
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
int		lexer(t_vars *vars);

/*
 **		lexer2.c
 */
void	word_handle(t_vars *vars, char **buf, char *cur_char);
void	space_handle(t_vars *vars, char **buf, char *cur_char);
void	escape_handle(t_vars *vars, char **buf, char *cur_char);
void	quoted_state_handle(t_vars *vars, char *cur_char);

/*
 **		token.c
 */
int		get_token_type(char c);
void	new_token(t_vars *vars, int type, char *data);
void	del_token(void *content);

#endif
