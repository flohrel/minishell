/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:30:48 by mtogbe            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/29 09:07:33 by flohrel          ###   ########.fr       */
=======
/*   Updated: 2021/05/29 18:07:51 by mtogbe           ###   ########.fr       */
>>>>>>> 0343944aaace6a3c24e98ef3ccdfa6b91daa0020
/*                                                                            */
/* ************************************************************************** */

#include "libft/memory.h"

void	*garbage_collector(size_t nmemb, size_t size, t_list **lst)
{
	void			*ptr;
	t_list			*new;

	if (!lst)
		return (NULL);
	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		return (NULL);
	new = ft_lstnew(ptr);
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_front(lst, new);
	return (ptr);
}
