/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:29:11 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 18:50:43 by mtogbe           ###   ########.fr       */
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

void	init_vars(t_vars *vars)
{
//	hist_import(vars);
	vars->lexer.tk_list = NULL;
	vars->lexer.buffer = NULL;
	vars->ptr_list = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	init(&vars, envp);
	init_term(&vars);
	vars.env = parse_env(envp, &vars);
	while (isatty(0))
	{
		init_vars(&vars);
		display_prompt();
		ft_readline(&vars);
		lexer(&vars, &vars.lexer);
		if (parser(&vars, &vars.lexer, &vars.parser) == 0)
		{
			tree_display(vars.parser.exec_tree, 0, 0);
			exec_ast(&vars, vars.parser.exec_tree);
		}
		free_ptr_lst(&vars.ptr_list);
	}
	free_unlisted_vars(&vars);
//	hist_export(vars);
	return (0);
}
