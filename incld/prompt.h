/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:39:56 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/28 21:33:26 by flohrel          ###   ########.fr       */
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

void	display_prompt(void);
void	ft_readline(t_vars *vars);

#endif
