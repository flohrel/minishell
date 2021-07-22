/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:56:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/21 03:51:03 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_token(t_parser *parser, int type)
{
	t_token	*token;

	token = (t_token *)parser->cur_tk->content;
	if (token->type != type)
		return (0);
	parser->cur_tk = parser->cur_tk->next;
	return (1);
}

char	*var_assignation(t_vars *vars, char *data, char *str)
{
	char	*var;
	char	tmp;

	tmp = *str;
	*str = '\0';
	var = get_env_value(data, vars->env);
	if (!var)
	{
		var = ft_strdup("\0");
		if (!var)
			return (NULL);
		add_to_ptrlst((void *)var, vars);
	}
	*str = tmp;
	return (var);
}

char	*exit_status_expansion(t_vars *vars, char **str, int exit_status)
{
	char	*var;

	var = ft_itoa(exit_status);
	add_to_ptrlst((void *)var, vars);
	(*str) += 2;
	return (var);
}

void	var_expansion(t_vars *vars, char **buffer, char **data)
{
	char	*var;
	char	*str;

	str = *data;
	if (*(str + 1) == '?')
		var = exit_status_expansion(vars, &str, vars->exit_status);
	else
	{
		while (*(str++))
		{
			if (!(*str) || (!ft_isalnum(*str) && (*str != '_')))
			{
				var = var_assignation(vars, *data + 1, str);
				if (!var)
					clean_exit(vars, NULL, 127);
				break ;
			}
		}
	}
	ft_strlcpy(*buffer, var, ft_strlen(var) + 1);
	if (ft_strlen(var))
		(*buffer) += ft_strlen(var) - 1;
	(*data) = str - 1;
}