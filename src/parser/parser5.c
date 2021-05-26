/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:07:59 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/27 01:45:31 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		redirection(t_vars *vars, t_parser *parser, int type, t_cmd *data)
{
	t_token	*token;
	t_token	*redir;
	t_list	*lst;

	parser->cur_tk = parser->cur_tk->next;
	token = (t_token *)parser->cur_tk->content;
	if (token->type != TK_WORD)
		return (-1);
	lst = lst_alloc(1, sizeof(*lst), &vars->ptr_list);
	if (lst == NULL)
		clean_exit(vars, errno);
	lst->next = NULL;
	redir = lst_alloc(1, sizeof(*redir), &vars->ptr_list);
	if (redir == NULL)
		clean_exit(vars, errno);
	redir->type = type;
	redir->data = token->data;
	lst->content = redir;
	ft_lstadd_back(&data->redir, lst);
	return (0);
}

void	argument(t_parser *parser, t_token *token, t_cmd *data)
{
	if (!data->path)
		data->path = token->data;
	else
		ft_lstadd_back(&data->arg, parser->cur_tk);
}

void	init_cmd_data(t_cmd *data)
{
	data->path = NULL;
	data->redir = NULL;
	data->arg = NULL;
}

t_ast	*cmd(t_vars *vars, t_parser *parser)
{
	t_ast	*node;
	t_cmd	*data;
	t_token	*token;

	data = lst_alloc(1, sizeof(*data), &vars->ptr_list);
	if (data == NULL)
		clean_exit(vars, errno);
	init_cmd_data(data);
	token = (t_token *)parser->cur_tk->content;
	while ((token->type == TK_WORD) || (token->type > TK_SEMI))
	{
		if ((token->type > TK_SEMI) &&
			(redirection(vars, parser, token->type, data) == -1))
			return (NULL);
		else
			argument(parser, token, data);
		parser->cur_tk = parser->cur_tk->next;
		token = (t_token *)parser->cur_tk->content;
	}
	node = tree_new_node(vars, NODE_CMD, data);
	return (node);
}
