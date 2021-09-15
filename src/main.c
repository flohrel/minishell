/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:29:11 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/15 14:48:24 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

void	sigint_handler(int signum)
{
	g_sig.exit_status = 128 + signum;
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(0) && !g_sig.is_child && g_sig.is_displayed)
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
	g_sig.is_child = 0;
	g_sig.is_displayed = 1;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		init_vars(&vars);
		ft_readline(&vars);
		if ((lexer(&vars, &vars.lexer) != -1)
			&& (astree_build(&vars, &vars.lexer, &vars.parser) != -1))
		{
			tree_display(vars.exec_tree, 0, 0);
			exec_ast(&vars, vars.exec_tree);
		}
		free_ptr_lst(&vars.ptr_list);
	}
}
