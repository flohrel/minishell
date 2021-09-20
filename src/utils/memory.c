/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 09:02:58 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/14 19:21:06 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*lst_alloc(size_t nmemb, size_t size, t_vars *vars)
{
	void	*ptr;

	ptr = garbage_collector(nmemb, size, &vars->ptr_list);
	if (ptr == NULL)
		clean_exit(vars, NULL, NULL, errno);
	return (ptr);
}

void	*add_to_ptrlst(void *content, t_vars *vars)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (NULL);
	ft_lstadd_front(&(vars->ptr_list), new);
	return (new);
}
