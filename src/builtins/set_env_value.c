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

#include "minishell.h"

t_env	*set_env_value(t_env *env, char *key, char *value)
{
	t_env	*head;
	t_env	*tmp;
	char	*stack;

	head = env;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			stack = tmp->value;
			free(stack);
			stack = ft_strdup(value);
			if (!stack)
				return (NULL);
			tmp->value = stack;
			return (head);
		}
		tmp = tmp->next;
	}
	return (head);
}
