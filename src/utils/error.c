/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 07:26:48 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/27 07:46:41 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.h"

int		syntax_error(t_token *token)
{
	ft_putstr_fd("bash: syntax error", STDERR_FILENO);
	if (token == NULL)
		ft_putstr_fd(": quote missing\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(" near unexpected token `", STDERR_FILENO);
		if (token->type == TK_NL)
			ft_putstr_fd("newline", STDERR_FILENO);
		else if (token->type == TK_DGREAT)
			ft_putstr_fd(">>", STDERR_FILENO);
		else
			ft_putchar_fd(get_token_char(token->type), STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	return (-1);
}
