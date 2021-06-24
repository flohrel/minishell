/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:01:08 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/24 20:04:21 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	swap_env(t_env *env)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = env->key;
	tmp_value = env->value;
	env->key = env->next->key;
	env->value = env->next->value;
	env->next->key = tmp_key;
	env->next->value = tmp_value;
}

void	print_sorted_env(t_env *env)
{
	t_env	*head;
	int		reset;

	env = envcpy(env);
	head = env;
	while (env && env->next)
	{
		reset = 0;
		if (ft_strcmp(env->key, env->next->key) > 0)
		{
			swap_env(env);
			reset = 1;
		}
		env = env->next;
		if (reset)
			env = head;
	}
	exp_print(head);
	free_env(head);
}
