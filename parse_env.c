/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:48:37 by mtogbe            #+#    #+#             */
/*   Updated: 2021/04/16 18:07:04 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_env	*parse_env(char **env)
{
	t_env	*result;
	t_env	*head;
	int		i;

	i = 0;
	result = malloc(sizeof(t_env));
	if (!result)
		return (NULL);
	head = result;
	while (env && env[i])
	{
		result->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		result->key	 = malloc((sizeof(char) * ft_strlen(env[i]) - ft_strlen(result->value)));
		ft_strlcat(result->key, env[i], ft_strlen(env[i]) - ft_strlen(result->value));
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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_env = parse_env(env);
	g_env = unset("TERM", g_env);
	print_env(g_env);
	pwd(g_env);
}
