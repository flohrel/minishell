/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:39:56 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:58:53 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include "ansi_colors.h"
# include "data.h"
# include "utils.h"

# define BUFFER_SIZE	4096
# define HIST_SIZE		500
# define HIST_FILE		".minish_history"
# define PROMPT			"minishell>> "

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

/*
**		history.c
*/
//void	hist_import(t_vars *vars);
//void	hist_export(t_vars *vars);
void	save_input(t_vars *vars, char *input);

#endif
