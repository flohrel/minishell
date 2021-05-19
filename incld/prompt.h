/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:39:56 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/30 03:36:36 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include "ansi_colors.h"
# include "data.h"
# include "exit.h"

# define BUFFER_SIZE	4096
# define PROMPT			BGRN"minishell>> "RESET

/*
**		prompt.c
*/
void	display_prompt(void);
void	init_term(t_vars *vars);
void	ft_readline(t_vars *vars);

/*
**		input.c
*/
int		input_handle(t_vars *vars, char *input, int size, int *index);

#endif
