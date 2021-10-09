/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:08:54 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/09 13:24:01 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	sigint_handler_f(int signum)
{
	g_sig.exit_status = 128 + signum;
}

void	sigint_handler(int signum)
{
	g_sig.exit_status = 128 + signum;
	write(STDERR_FILENO, "\n", 1);
	if (isatty(0))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signum)
{
	g_sig.exit_status = 128 + signum;
	(void)signum;
	write(1, "\033[2D\033[0K", 8);
}

void	sigquit_handler_f(int signum)
{
	if (signum == 3)
		ft_putstr_fd("Quit (core dumped)\n  ", STDERR_FILENO);
	write(1, "\033[2D\033[0K", 8);
	g_sig.exit_status = 128 + signum;
}
