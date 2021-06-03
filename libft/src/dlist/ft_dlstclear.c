/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:51:19 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:04:36 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*lptr;
	t_dlist	*next;

	if (lst && *lst && del)
	{
		lptr = *lst;
		while (lptr)
		{
			next = lptr->next;
			ft_dlstdelone(lptr, del);
			lptr = next;
		}
		*lst = NULL;
	}
}
