/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 14:24:55 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	display_prompt(void)
{
	if (isatty(STDOUT_FILENO))
	{
		ft_putstr_fd(BGRN, STDERR_FILENO);
		ft_putstr_fd(PROMPT, STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
	}
}

void	ft_readline(t_vars *vars)
{
	t_dlist	*entry;
	char	buffer[BUFFER_SIZE];
	int		ret;
	int		i;

	i = 0;
	ret = -1;
	entry = ft_dlstnew(NULL);
	if (!entry)
		clean_exit(vars, errno);
	while (ret)
	{
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		if (read(0, &buffer[i], 4) < 0)
			clean_exit(vars, errno);
		ret = input_handle(vars, &buffer[i], &i);
	}
	vars->lexer.buffer = lst_alloc(i + 1, sizeof(*(vars->lexer.buffer)), vars);
	ft_strlcpy(vars->lexer.buffer, buffer, i + 1);
	save_input(vars, &vars->history, entry, buffer);
}
