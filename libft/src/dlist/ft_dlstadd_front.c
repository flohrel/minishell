/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:09:13 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 14:04:34 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	if (alst && new)
	{
		if (*alst)
			(*alst)->prev = new;
		new->next = *alst;
		*alst = new;
	}
}
