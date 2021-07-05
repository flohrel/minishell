/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:29 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/05 16:49:56 by flohrel          ###   ########.fr       */
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
void	lexer(t_vars *vars, t_lexer *lexer);
void	lexer_init(t_vars *vars, void (*token_handle[5])(t_vars *, char **));
void	quote_handle(t_vars *vars, char *buf);

/*
 **		lexer1.c
 */
void	redirection_handle(t_vars *vars, int tk_type, char **buf);
void	job_token_handle(int tk_type, t_vars *vars, char **buf);
void	word_handle(t_vars *vars, char **buf);
void	space_handle(t_vars *vars, char **buf);
void	escape_handle(t_vars *vars, char **buf);

#endif
