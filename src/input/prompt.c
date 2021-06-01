/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/01 17:37:04 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	display_prompt(void)
{
	ft_putstr_fd(BGRN, STDERR_FILENO);
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

void	init_term(t_vars *vars)
{
	t_term	*termios;
	char	*term_type;

	termios = &vars->termios;
	if (tcgetattr(STDIN_FILENO, &termios->original) == -1)
		clean_exit(vars, errno);
	termios->current = termios->original;
	termios->current.c_lflag &= ~(ICANON);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios->current))
		clean_exit(vars, errno);
	term_type = getenv("TERM");
	if (term_type == NULL || tgetent(NULL, term_type) <= 0)
		clean_exit(vars, 0);
}

/*void	history_save(t_vars *vars, char *buffer)
{
	t_dlist	*cmdline;
	char	*copy;

	if (*buffer)
	{
		copy = ft_strdup(buffer);
		if (copy == NULL)
			clean_exit(vars, errno);
		cmdline = ft_dlstnew(copy);
		if (cmdline == NULL)
			clean_exit(vars, errno);
		ft_dlstadd_front(vars->history);
	}
}*/

void	ft_readline(t_vars *vars)
{
	char	buffer[BUFFER_SIZE];
	int		size;
	int		ret;
	int		i;

	i = 0;
	ret = -1;
	while (ret)
	{
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		size = read(0, &buffer[i], 4);
		ret = input_handle(vars, &buffer[i], size, &i);
	}
	vars->lexer.buffer = lst_alloc(i + 1, sizeof(*(vars->lexer.buffer)), vars);
	ft_strlcpy(vars->lexer.buffer, buffer, i + 1);
//	history_save(vars->history, buffer);
}
