/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:52:49 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/21 03:06:37 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*make_block(char *key, char *value)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (NULL);
	result->value = ft_strdup(value);
	if (!result->value)
		return (NULL);
	result->key = ft_strdup(key);
	if (!result->key)
		return (NULL);
	result->next = NULL;
	return (result);
}

int	set_value(t_env *tmp, char *value)
{
	char	*stack;

	if (!tmp)
		return (-1);
	stack = tmp->value;
	free(stack);
	if (value)
		stack = ft_strdup(value);
	else
		stack = value;
	if (value && !stack)
		return (-1);
	tmp->value = stack;
	return (1);
}

t_env	*makeblock(char *key, char *value)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (NULL);
	if (value)
	result->value = ft_strdup(value);
	if (value && !result->value)
		return (NULL);
	result->key = ft_strdup(key);
	if (!result->key)
		return (NULL);
	return (result);
}

t_env	*set_env_value(t_env *env, char *key, char *value)
{
	t_env	*head;
	t_env	*tmp;

	head = env;
	tmp = env;
	if (!tmp)
		return (makeblock(key, value));
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (set_value(tmp, value) < 0)
				return (NULL);
			return (head);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = make_block(key, value);
	if (!tmp->next)
		return (NULL);
	return (head);
}
