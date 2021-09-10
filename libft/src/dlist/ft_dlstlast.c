/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:20:00 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:00:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
