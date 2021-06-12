/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:39:56 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/12 11:01:31 by flohrel          ###   ########.fr       */
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
**		input.c
*/
void	ft_readline(t_vars *vars);

#endif
