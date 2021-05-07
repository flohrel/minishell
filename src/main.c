/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:29:11 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/07 17:04:58 by flohrel          ###   ########.fr       */
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
	vars->lexer.tk_list = NULL;
	vars->lexer.buffer = NULL;
}

int		main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	(void)envp;
	errno = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	init_term(&vars);
	while (1)
	{
		init_vars(&vars);
		display_prompt();
		ft_readline(&vars);
		lexer(&vars, &vars.lexer);
		parser(&vars, &vars.lexer, &vars.parser);
		display_token_list(&vars.lexer);
		free_vars(&vars);
	}
	return (0);
}
