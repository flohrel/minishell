/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 19:38:57 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:11:16 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new_lst;
	t_dlist	*tmp;

	if (!lst || !f)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		tmp = ft_dlstnew(f(lst->content));
		if (!tmp)
		{
			ft_dlstclear(&new_lst, del);
			return (NULL);
		}
		ft_dlstadd_back(&new_lst, tmp);
		lst = lst->next;
	}
	return (new_lst);
}
