/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:29:11 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/30 17:11:38 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;

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
