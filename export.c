/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:14:46 by mtogbe            #+#    #+#             */
/*   Updated: 2021/04/16 17:34:36 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char *str, t_env *env)
{
	t_env	*result;
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	result = malloc(sizeof(t_env));
	result->value = ft_strdup(ft_strchr(str, '=') + 1);
	result->key	 = malloc((sizeof(char) * ft_strlen(str) - ft_strlen(result->value)));
	ft_strlcat(result->key, str, ft_strlen(str) - ft_strlen(result->value));
	result->next = NULL;
	tmp->next = result;
	return (1);
}
