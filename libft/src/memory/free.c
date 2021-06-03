/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:57:48 by mtogbe            #+#    #+#             */
/*   Updated: 2021/05/26 18:43:12 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/memory.h"

void			free_ptr(void *ptr, t_list **head)
{
	t_list	*lst;
	t_list	*tmp;

	lst = *head;
	if (lst->content == ptr)
	{
		*head = lst->next;
		free(lst->content);
		free(lst);
		return ;
	}
	while (lst && lst->next)
	{
		if (lst->next->content == ptr)
		{
			tmp = lst->next;
			lst->next = tmp->next;
			free(tmp->content);
			free(tmp);
			return ;
		}
		lst = lst->next;
	}
}

void			free_ptr_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
}
