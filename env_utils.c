/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:58:50 by mtogbe            #+#    #+#             */
/*   Updated: 2021/04/21 17:20:03 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_env **env)
{
	t_env	*head;
	char	*tmp;
	int		reset;

	reset = 0;
	head = *env;
	while (*env && (*env)->next)
	{
		reset = 0;
		if (ft_strcmp((*env)->key, (*env)->next->key) > 0)
		{
			tmp = (*env)->key;
			(*env)->key = (*env)->next->key;
			(*env)->next->key = tmp;
			reset = 1;
		}
		*env = (*env)->next;
		if (reset)
			*env = head;
	}
	print_env(head);
}
