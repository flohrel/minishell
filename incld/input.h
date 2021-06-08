/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:39:56 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/08 07:49:36 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <curses.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ansi_colors.h"
# include "data.h"
# include "utils.h"

# define BUFFER_SIZE	4096
# define PROMPT			"\e[1;32mminishell>> \e[0m"

/*
**		prompt.c
*/
void	display_prompt(void);
void	ft_readline(t_vars *vars);

/*
**		input.c
*/
int		input_handle(t_vars *vars, char *buffer, int *index);

/*
**		history.c
*/
void	get_hist_entry(t_hist *history, bool is_prev);

#endif
