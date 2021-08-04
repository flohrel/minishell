/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:29:11 by flohrel           #+#    #+#             */
/*   Updated: 2021/08/04 03:34:44 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status;

void	sigint_handler(int signum)
{
	exit_status = 128 + signum;
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(0))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signum)
{
	exit_status = 128 + signum;
	write(1, "\033[2D\033[0K", 8);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	init(&vars, envp);
	while (1)
	{
		init_vars(&vars);
		ft_readline(&vars);
		lexer(&vars, &vars.lexer);
		if (parser(&vars, &vars.lexer, &vars.parser) == 0)
			exec_ast(&vars, vars.parser.exec_tree);
		free_ptr_lst(&vars.ptr_list);
	}
}
