/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:29 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/05 21:06:44 by flohrel          ###   ########.fr       */
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

/*
 **		lexer1.c
 */
void	redirection_handle(t_vars *vars, int tk_type, char **buf);
void	job_handle(t_vars *vars, int tk_type, char **buf);
void	word_handle(t_vars *vars, int tk_type, char **buf);
void	space_handle(t_vars *vars, int tk_type, char **buf);
void	escape_handle(t_vars *vars, int tk_type, char **buf);

#endif
