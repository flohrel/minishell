/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/18 04:01:55 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_cmd(t_cmd **data)
{
	if ((*data)->path)
		free((*data)->path);
	free(*data);
}

void	free_tree(t_ast **node)
{
	if (*node == NULL)
		return ;
	free_tree(&((*node)->left));
	free_tree(&((*node)->right));
	if ((*node)->type & NODE_CMD)
		free_cmd(&(*node)->data);
	free(*node);
}

void	free_vars(t_lexer *lexer, t_parser *parser)
{
	ft_lstclear(&(lexer->tk_list), del_token);
	if (lexer->buffer)
		free(lexer->buffer);
	if (parser->exec_tree)
		free_tree(&(parser->exec_tree));
}

void	clean_exit(t_vars *vars, int status)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &vars->termios.original);
	free_vars(&vars->lexer, &vars->parser);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
