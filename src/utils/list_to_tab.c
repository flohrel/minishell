/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 18:30:44 by mtogbe            #+#    #+#             */
/*   Updated: 2021/05/31 18:59:24 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_tab(t_list *lst, t_vars *vars)
{
	char	**result;
	int		i;
	int		size;
	t_token	*token;

	size = ft_lstsize(lst);
	i = 0;
	result = lst_alloc(size + 1, sizeof(char *), vars);
	if (!result)
		return (NULL);
	while (i < size)
	{
		token = (t_token *)lst->content;
		result[i++] = token->data;
		lst = lst->next;
	}
	result[i] = NULL;
	return (result);
}
