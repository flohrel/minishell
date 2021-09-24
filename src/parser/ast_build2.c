/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 02:07:59 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/24 18:02:05 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	redirection(t_vars *vars, t_parser *parser, int *type, t_param *data)
{
	t_token	*token;
	t_token	*redir;
	t_list	*lst;

	parser->cur_tk = parser->cur_tk->next;
	token = (t_token *)parser->cur_tk->content;
	if (token->type != TK_WORD)
		return (-1);
	if (check_flag(*type, TK_DLESS)
		&& (ft_strchr(token->data, '\'') || ft_strchr(token->data, '\"')))
		*type = (TK_DLESS2 | TK_REDIR);
	lst = lst_alloc(1, sizeof(*lst), vars);
	lst->next = NULL;
	redir = lst_alloc(1, sizeof(*redir), vars);
	redir->type = *type;
	redir->data = token->data;
	lst->content = redir;
	ft_lstadd_back(&data->redir, lst);
	return (0);
}

bool	is_valid_name(char *data, char *end)
{
	if ((data == end) || ft_isdigit(*data) || (*data == '$'))
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

	ptr = ft_strchr(token->data, '=');
	if (ptr && (is_valid_name(token->data, ptr) == true) && !data->arg)
		dest_list = &data->assign;
	else
		dest_list = &data->arg;
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
	data->io.flag = 0;
	data->io.delim = NULL;
	data->io.std_in = -1;
	data->io.std_out = -1;
	data->io.dup_in = -1;
	data->io.dup_out = -1;
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
	while ((token->type == TK_WORD) || check_flag(token->type, TK_REDIR))
	{
		if (token->type == TK_WORD)
			argument(vars, token, data);
		else if (redirection(vars, parser, &token->type, data) == -1)
			return (NULL);
		parser->cur_tk = parser->cur_tk->next;
		token = (t_token *)parser->cur_tk->content;
	}
	if (!data->arg && !data->redir && !data->assign)
		return (NULL);
	return (tree_new_node(vars, NODE_CMD, data));
}
