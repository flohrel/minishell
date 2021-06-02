/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:52:49 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/02 19:37:50 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			tmp->value = value;
			return (head);
		}
		tmp = tmp->next;
	}
	return (head);
}
