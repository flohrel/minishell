/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:58:03 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/06 17:47:54 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	clean_empty_word(t_vars *vars, char **data, char *buffer)
{
	bool	has_quotes;
	size_t	len;

	has_quotes = false;
	if (ft_strchr(*data, '\'') || ft_strchr(*data, '\"'))
		has_quotes = true;
	if (*buffer || has_quotes)
	{
		len = ft_strlen(buffer);
		*data = lst_alloc(len + 1, sizeof(*buffer), vars);
		ft_strlcpy(*data, buffer, len + 1);
	}
	else
	{
		delete_empty_token(&vars->lexer, &vars->parser);
		return (1);
	}
	return (0);
}

void	path_expansion(t_vars *vars, char *str, char *buffer)
{
	char	c;
	char	*s;
	char	*buf;
	int		state;

	s = str;
	buf = buffer;
	state = ST_GENERAL;
	while (*str)
	{
		c = *str;
		state_check(&state, c);
		if ((c == '*') && (state == ST_GENERAL))
		{
			wildcard(vars, buf, s);
			return ;
		}
		else
		{
			*buffer = c;
			buffer++;
		}
		str++;
	}
	*buffer = '\0';
}

void	param_expansion(t_vars *vars, char *str, char *buffer)
{
	char	c;
	int		state;

	state = ST_GENERAL;
	while (*str)
	{
		c = *str;
		state_check(&state, c);
		if ((c == '$') && (state != ST_QUOTE) && (*(str + 1) != '\0'))
			var_expansion(vars, &buffer, &str);
		else
		{
			*buffer = c;
			buffer++;
		}
		str++;
	}
	*buffer = '\0';
}

void	parse_list(t_vars *vars, t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = (t_token *)lst->content;
		parse_word(vars, &token->data);
		lst = lst->next;
	}
}

void	parse_word(t_vars *vars, char **word)
{
	char	buffer[2][BUFFER_SIZE];
	int		len;

	param_expansion(vars, *word, buffer[0]);
	path_expansion(vars, buffer[0], buffer[1]);
	len = ft_strlen(buffer[1]);
	if (len == 0)
	{
		*word = NULL;
		return ;
	}
	*word = lst_alloc(len + 1, sizeof(*word), vars);
	ft_strlcpy(*word, buffer[1], len + 1);
}

void	parse_param(t_vars *vars, t_param *param)
{
	if (param->path)
		parse_word(vars, &param->path);
	parse_list(vars, param->redir);
	parse_list(vars, param->arg);
	parse_list(vars, param->assign);
}
