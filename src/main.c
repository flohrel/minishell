/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:29:11 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/22 17:06:33 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	sigint_handler(int signum)
{
	g_sig.exit_status = 128 + signum;
	//if (g_sig.minishlvl == 0)
		write(STDERR_FILENO, "\n", 1);
	if (isatty(0)) //&& !g_sig.is_child && g_sig.is_displayed)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signum)
{
	g_sig.exit_status = 128 + signum;
	write(1, "\033[2D\033[0K", 8);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	init(&vars, envp);
	while (1)
	{
		if (g_sig.exit_status == 130)
			ft_putstr_fd("\n", STDERR_FILENO);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		init_vars(&vars);
		ft_readline(&vars);
		if ((lexer(&vars, &vars.lexer) != -1)
			&& (astree_build(&vars, &vars.lexer, &vars.parser) != -1))
			exec_ast(&vars, vars.exec_tree);
		free_ptr_lst(&vars.ptr_list);
	}
}
