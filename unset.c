/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:36:41 by mtogbe            #+#    #+#             */
/*   Updated: 2021/04/16 18:16:01 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*remove_mid(t_env *env, char *key)
{
	t_env	*stack;
	t_env	*head;

	head = env;
	while (env && env->next)
	{
		if (ft_strcmp(key, env->key) == 0)
		{
			stack = env->next;
			env->next = env->next->next;
			free(stack);
		}
		env = env->next;
	}
	return (head);
}

t_env	*unset(char *key, t_env *env)
{
	t_env	*tmp;
	t_env	*stack;
	t_env	*head;

	head = env;
	if (get_env_value(key, env))
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			stack = env;
			env = env->next;
			free(env);
			return (env);
		}
		tmp = remove_mid(env, key);
		head = tmp;
		while (tmp->next)
			tmp = tmp->next;
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp);
			tmp = NULL;
		}
	}
	return (head);
}
