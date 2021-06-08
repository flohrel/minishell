/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:02:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/08 07:49:36 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	get_hist_entry(t_hist *history, bool is_prev)
{
	if (is_prev)
		history->cur = history->cur->prev;
	else
		history->cur = history->cur->next;
	if (history->cur)
		ft_putstr_fd((char *)history->cur->content, STDIN_FILENO);
}
