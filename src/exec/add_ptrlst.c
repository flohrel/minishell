/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ptrlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:13:52 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/04 17:14:02 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*add_to_ptrlst(void *content, t_vars *vars)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (NULL);
	ft_lstadd_front(&(vars->ptr_list), new);
	return (new);
}

