/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:48:37 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/01 15:37:19 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_envblock(char *str, t_env *result, t_vars *vars)
{
	t_list	*new;
	int		len;

	result->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!(result->value))
		return (NULL);
	new = ft_lstnew((void *)(result->value));
	if (!new)
		return (NULL);
	ft_lstadd_front(&vars->ptr_list, new);
	len = ft_strlen(str) - ft_strlen(result->value);
	result->key = lst_alloc(len, sizeof(char), vars);
	if (!(result->key))
		return (NULL);
	ft_strlcat(result->key, str, len);
	return (result);
}

t_env	*parse_env(char **env, t_vars *vars)
{
	t_env	*result;
	t_env	*head;
	int		i;

	i = 0;
	result = lst_alloc(1, sizeof(t_env), vars);
	if (!result)
		return (NULL);
	head = result;
	while (env && env[i])
	{
		result = new_envblock(env[i], result, vars);
		if (!result)
			return (NULL);
		if (env[++i])
		{
			result->next = malloc(sizeof(t_env));
			if (!result->next)
				return (NULL);
		}
		else
			result->next = NULL;
		result = result->next;
	}
	return (head);
}
