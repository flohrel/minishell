/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:43:21 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/14 14:42:29 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

static t_dlist	*merge(t_dlist *left, t_dlist *right,
		int (*cmp)(void *, void *))
{
	t_dlist	*merged;
	t_dlist	*lst;

	merged = NULL;
	while (left && right)
	{
		if (cmp(left->content, right->content) > 0)
		{
			lst = right;
			right = right->next;
		}
		else
		{
			lst = left;
			left = left->next;
		}
		lst->next = NULL;
		ft_dlstadd_back(&merged, lst);
	}
	if (left)
		ft_dlstadd_back(&merged, left);
	else
		ft_dlstadd_back(&merged, right);
	return (merged);
}

void	ft_dlstsort(t_dlist **lst, int (*cmp)(void *, void *))
{
	int		size;
	int		mid;
	t_dlist	*left;
	t_dlist	*right;
	t_dlist	*ptr;

	ptr = *lst;
	size = ft_dlstsize(ptr);
	if (size == 1)
		return ;
	left = ptr;
	mid = size / 2;
	while (--mid)
		ptr = ptr->next;
	right = ptr->next;
	ptr->next = NULL;
	ft_dlstsort(&left, cmp);
	ft_dlstsort(&right, cmp);
	*lst = merge(left, right, cmp);
}
