/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:07:59 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/18 17:17:37 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		redirection(t_vars *vars, t_parser *parser, t_cmd *data, int type)
{
	t_token	*token;
	t_token	*rd_data;
	t_list	*lst;

	parser->cur_tk = parser->cur_tk->next;
	token = (t_token *)parser->cur_tk->content;
	if (token->type != 0)
		return (-1);
	rd_data = ft_calloc(1, sizeof(*rd_data));
	if (!rd_data)
		clean_exit(vars, errno);
	rd_data->type = type;
	rd_data->data = ft_strdup(token->data);
	if (!rd_data->data)
		clean_exit(vars, errno);
	lst = ft_lstnew(rd_data);
	ft_lstadd_back(&data->redir, lst);
	return (0);
}

void	argument(t_vars *vars, t_token *token, t_cmd *data)
{
	char	*arg;
	t_list	*lst;

	if (!data->path)
		data->path = ft_strdup(token->data);
	else
	{
		arg = ft_strdup(token->data);
		if (!arg)
			clean_exit(vars, errno);
		lst = ft_lstnew(arg);
		if (!lst)
			clean_exit(vars, errno);
		ft_lstadd_back(&data->arg, lst);
	}
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

	data = ft_calloc(1, sizeof(*data));
	if (data == NULL)
		clean_exit(vars, errno);
	init_cmd_data(data);
	token = (t_token *)parser->cur_tk->content;
	while (!token->type || (token->type > TK_SEMI))
	{
		if ((token->type > TK_SEMI) &&
			(redirection(vars, parser, data, token->type) == -1))
		{
			free_cmd_node(data);
			return (NULL);
		}
		else
			argument(vars, token, data);
		parser->cur_tk = parser->cur_tk->next;
		token = (t_token *)parser->cur_tk->content;
	}
	node = tree_new_node(vars, NODE_CMD, data);
	return (node);
}
