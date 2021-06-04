/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:48:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 18:49:37 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_term(t_vars *vars)
{
	t_term	*termios;
	char	*term_type;

	termios = &vars->termios;
	if (tcgetattr(STDIN_FILENO, &termios->original) == -1)
		clean_exit(vars, errno);
	termios->current = termios->original;
	termios->current.c_lflag &= ~(ICANON);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios->current))
		clean_exit(vars, errno);
	term_type = getenv("TERM");
	if (term_type == NULL || tgetent(NULL, term_type) <= 0)
		clean_exit(vars, 0);
}

void	init(t_vars *vars, char **envp)
{
	errno = 0;
	vars->env = parse_env(envp, vars);
	vars->history.lst = NULL;
	vars->history.cur = NULL;
	init_term(vars);
}
