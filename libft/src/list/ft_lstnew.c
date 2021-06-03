/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:01:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:54:35 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/list.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (new);
	new->content = content;
	new->next = NULL;
	return (new);
}
