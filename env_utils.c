/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:58:50 by mtogbe            #+#    #+#             */
/*   Updated: 2021/04/21 18:04:43 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_env **env)
{
	t_env	*head;
	char	*tmp_key;
	char	*tmp_value;
	int		reset;

	reset = 0;
	head = *env;
	while (*env && (*env)->next)
	{
		reset = 0;
		if (ft_strcmp((*env)->key, (*env)->next->key) > 0)
		{
			tmp_key = (*env)->key;
			tmp_value = (*env)->value;
			(*env)->key = (*env)->next->key;
			(*env)->value = (*env)->next->value;
			(*env)->next->key = tmp_key;
			(*env)->next->value = tmp_value;
			reset = 1;
		}
		*env = (*env)->next;
		if (reset)
			*env = head;
	}
	print_env(head);
}
