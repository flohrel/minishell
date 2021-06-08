/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:07:59 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/08 08:57:21 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	redirection(t_vars *vars, t_parser *parser, int type, t_param *data)
{
	t_token	*token;
	t_token	*redir;
	t_list	*lst;

	parser->cur_tk = parser->cur_tk->next;
	token = (t_token *)parser->cur_tk->content;
	if (token->type != TK_WORD)
		return (-1);
	lst = lst_alloc(1, sizeof(*lst), vars);
	lst->next = NULL;
	redir = lst_alloc(1, sizeof(*redir), vars);
	redir->type = type;
	redir->data = token->data;
	lst->content = redir;
	ft_lstadd_back(&data->redir, lst);
	return (0);
}

bool	is_valid_name(char *data, char *end)
{
	if ((data == end) || ft_isdigit(*data))
		return (false);
	else if (*(end - 1) == '+')
	{
		end--;
		if (data == end)
			return (false);
	}
	while (data != end)
	{
		if (!ft_isalnum(*data))
			return (false);
		data++;
	}
	return (true);
}

void	argument(t_vars *vars, t_token *token, t_param *data)
{
	t_list	**dest_list;
	t_list	*lst;
	t_token	*param;
	char	*ptr;

	dest_list = &data->arg;
	if (data->path == NULL)
	{
		ptr = ft_strchr(token->data, '=');
		if (ptr && (is_valid_name(token->data, ptr) == true))
			dest_list = &data->assign;
		else
		{
			data->path = token->data;
			return ;
		}
	}
	lst = lst_alloc(1, sizeof(*lst), vars);
	lst->next = NULL;
	param = lst_alloc(1, sizeof(*param), vars);
	param->type = TK_WORD;
	param->data = token->data;
	lst->content = param;
	ft_lstadd_back(dest_list, lst);
}

t_param	*init_cmd_param(t_vars *vars)
{
	t_param	*data;

	data = lst_alloc(1, sizeof(*data), vars);
	data->path = NULL;
	data->redir = NULL;
	data->arg = NULL;
	data->assign = NULL;
	return (data);
}

t_ast	*cmd(t_vars *vars, t_parser *parser)
{
	t_param	*data;
	t_token	*token;

	token = (t_token *)parser->cur_tk->content;
	if (token->type < 0)
		return (NULL);
	data = init_cmd_param(vars);
	while ((token->type == TK_WORD) || (token->type > TK_SEMI))
	{
		if (token->type == TK_WORD)
			argument(vars, token, data);
		else if (redirection(vars, parser, token->type, data) == -1)
			return (NULL);
		parser->cur_tk = parser->cur_tk->next;
		token = (t_token *)parser->cur_tk->content;
	}
	return (tree_new_node(vars, NODE_CMD, data));
}
