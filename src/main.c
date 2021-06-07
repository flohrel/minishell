/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:29:11 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/07 18:22:31 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	display_prompt();
}

void	sigquit_handler(int signum)
{
	(void)signum;
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
	while (isatty(0))
	{
		init_vars(&vars);
		display_prompt();
		ft_readline(&vars);
		lexer(&vars, &vars.lexer);
		if (parser(&vars, &vars.lexer, &vars.parser) == 0)
		{
			tree_display(vars.parser.exec_tree, 0, 0);
//			exec_ast(&vars, vars.parser.exec_tree);
		}
		free_ptr_lst(&vars.ptr_list);
	}
	free_unlisted_vars(&vars);
//	hist_export(vars);
	return (0);
}
