/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/19 17:58:09 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->data)
		free(token->data);
}

void	clean_exit(t_vars *vars, int status)
{
	ft_lstclear(&vars->lexer.tokens, del_token);
	free(vars->lexer.buffer);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
