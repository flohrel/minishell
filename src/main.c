/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:29:11 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/16 18:05:17 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		vars.lexer.buffer = NULL;
		write(1, "minishell>> ", 12);
		get_next_line(STDIN_FILENO, &vars.lexer.buffer);
		lexer(&vars);
		free(vars.lexer.buffer);
	}
	return (0);
}
