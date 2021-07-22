/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:01:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 00:51:17 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*new;

	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (new);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
