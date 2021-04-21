/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:29 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/20 14:22:51 by flohrel          ###   ########.fr       */
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
 **		token.c
 */
int		get_token_type(char c);
t_token	*new_token(int type);
void	del_token(void *content);

#endif
