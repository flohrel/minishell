/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:58:50 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/18 15:40:53 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

t_env	*envcpy(t_env *env)
{
	t_env	*result;
	t_env	*head;

	if (!env)
		return (NULL);
	result = blockcpy(env);
	if (!result)
		return (NULL);
	head = result;
	env = env->next;
	while (env)
	{
		result->next = blockcpy(env);
		if (!result->next)
			return (NULL);
		result = result->next;
		env = env->next;
	}
	result->next = NULL;
	return (head);
}

t_env	*blockcpy(t_env *env)
{
	t_env	*result;

	result = malloc(sizeof(t_env));
	if (!result)
		return (NULL);
	result->key = ft_strdup(env->key);
	if (!result->key)
		return (NULL);
	result->value = ft_strdup(env->value);
	if (!result->value)
		return (NULL);
	result->next = env->next;
	return (result);
}

void	free_block(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	free_env(t_env *env)
{
	t_env	*stack;

	while (env)
	{
		stack = env;
		env = env->next;
		free_block(stack);
	}
}

void	print_sorted_env(t_env *env)
{
	t_env	*head;
	char	*tmp_key;
	char	*tmp_value;
	int		reset;

	env = envcpy(env);
	head = env;
	while (env && env->next)
	{
		reset = 0;
		if (ft_strcmp(env->key, env->next->key) > 0)
		{
			tmp_key = env->key;
			tmp_value = env->value;
			env->key = env->next->key;
			env->value = env->next->value;
			env->next->key = tmp_key;
			env->next->value = tmp_value;
			reset = 1;
		}
			env = env->next;
		if (reset)
			env = head;
	}
	exp_print(head);
	free_env(head);
}
