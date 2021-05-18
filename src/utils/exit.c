/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:58:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/18 17:11:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	del_arg(void *content)
{
	char	*arg;

	arg = (char *)content;
	if (arg)
		free(arg);
}

void	free_cmd_node(t_cmd *data)
{
	if (data->path)
		free(data->path);
	ft_lstclear(&data->redir, del_token);
	ft_lstclear(&data->arg, del_arg);
}

void	free_vars(t_lexer *lexer, t_parser *parser)
{
	ft_lstclear(&(lexer->tk_list), del_token);
	if (lexer->buffer)
		free(lexer->buffer);
	if (parser->exec_tree)
		tree_delete_node(parser->exec_tree);
}

void	clean_exit(t_vars *vars, int status)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &vars->termios.original);
	free_vars(&vars->lexer, &vars->parser);
	if (errno)
		printf("%s\n", strerror(errno));
	exit(128 + status);
}
