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
	char	*input;
	t_lexer	lexbuf;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = NULL;
		write(1, "minishell>> ", 12);
		get_next_line(STDIN_FILENO, &input);
		lexer(input, &lexbuf);
		free(input);
	}
	return (0);
}
