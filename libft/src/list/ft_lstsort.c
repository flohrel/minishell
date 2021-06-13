/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 16:43:21 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/12 17:00:27 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/list.h"

static t_list	*merge(t_list *left, t_list *right, int (*cmp)(void *, void *))
{
	t_list	*merged;
	t_list	*lst;

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
		ft_lstadd_back(&merged, lst);
	}
	if (left)
		ft_lstadd_back(&merged, left);
	else
		ft_lstadd_back(&merged, right);
	return (merged);
}

void	ft_lstsort(t_list **lst, int (*cmp)(void *, void *))
{
	int		size;
	int		mid;
	t_list	*left;
	t_list	*right;
	t_list	*ptr;

	ptr = *lst;
	size = ft_lstsize(ptr);
	if (size == 1)
		return ;
	left = ptr;
	mid = size / 2;
	while (--mid)
		ptr = ptr->next;
	right = ptr->next;
	ptr->next = NULL;
	ft_lstsort(&left, cmp);
	ft_lstsort(&right, cmp);
	*lst = merge(left, right, cmp);
}
