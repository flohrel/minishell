/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:48:37 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/18 15:27:06 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	new_envblock(char *str, t_env *result)
{
	int		len1;
	int		len2;
	char	*chr;

	chr = ft_strchr(str, '=');
	if (!chr || chr == str)
		return (-1);
	chr = chr + 1;
	if (!chr)
		chr = "\0";
	result->value = ft_strdup(chr);
	if (!(result->value))
		return (0);
	len1 = ft_strlen(str);
	len2 = ft_strlen(result->value);
	result->key = malloc((len1 - len2) * sizeof(char));
	if (!(result->key))
		return (0);
	(result->key)[0] = '\0';
	ft_strlcat(result->key, str, len1 - len2);
	result->next = NULL;
	return (1);
}

t_env	*parse_env(char **env)
{
	t_env	*result;
	t_env	*head;
	int		i;

	i = 0;
	result = malloc(1 * sizeof(t_env));
	if (!result)
		return (NULL);
	head = result;
	while (env && env[i])
	{
		new_envblock(env[i], result);
		if (!result)
			return (NULL);
		if (env[++i])
		{
			result->next = malloc(sizeof(t_env));
			if (!result->next)
				return (NULL);
		}
		else
			result->next = NULL;
		result = result->next;
	}
	return (head);
}
