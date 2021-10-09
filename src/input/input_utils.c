/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:32:35 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/30 17:28:42 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*display_prompt(void)
{
	if (isatty(0))
	{
		if (!g_sig.exit_status)
			return (readline(PROMPT1));
		else
			return (readline(PROMPT2));
	}
	else
		return (readline(NULL));
}

int	heredoc_error_msg(t_vars *vars, char *delim, char *line_read)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(get_nline(vars), STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	free(line_read);
	return (0);
}
