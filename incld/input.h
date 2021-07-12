/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:39:56 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/08 15:05:04 by flohrel          ###   ########.fr       */
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

/*
**		input.c
*/
void	ft_readline(t_vars *vars);
int		input_handle(char *line_read, char *delim, char *buffer, int *index);
void	readline_hdoc(t_vars *vars, char *delim);

#endif
