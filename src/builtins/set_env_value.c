/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:52:49 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/11 17:34:31 by mtogbe           ###   ########.fr       */
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

	stack = tmp->value;
	free(stack);
	stack = ft_strdup(value);
	if (!stack)
		return (-1);
	tmp->value = stack;
	return (1);
}

t_env	*set_env_value(t_env *env, char *key, char *value)
{
	t_env	*head;
	t_env	*tmp;

	head = env;
	tmp = env;
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
