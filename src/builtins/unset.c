/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:36:41 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/01 15:33:27 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*remove_mid(t_env *env, char *key)
{
	t_env	*stack;
	t_env	*head;

	head = env;
	while (env && env->next && env->next->next)
	{
		if (ft_strcmp(key, env->next->key) == 0)
		{
			stack = env->next;
			env->next = env->next->next;
			free_block(stack);
		}
		env = env->next;
	}
	return (head);
}

static t_env	*unset_key(char *key, t_env *env)
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
			free_block(stack);
			return (env);
		}
		tmp = remove_mid(env, key);
		head = tmp;
		while (tmp && tmp->next && tmp->next->next)
			tmp = tmp->next;
		if (ft_strcmp(tmp->next->key, key) == 0)
		{
			free_block(tmp->next);
			tmp->next = NULL;
		}
	}
	return (head);
}

int	unset(char **args, t_vars *vars)
{
	vars->env = unset_key(args[0], vars->env);
	return (1);
}
