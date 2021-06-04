/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:02:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 14:18:34 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*void	hist_import(t_vars *vars)
{
}

void	hist_export(t_vars *vars)
{
}*/

void	get_hist_entry(t_hist *history, bool is_prev)
{
	if (is_prev)
		history->cur = history->cur->prev;
	else
		history->cur = history->cur->next;
	if (history->cur)
		ft_putstr_fd((char *)history->cur->content, STDOUT_FILENO);
}

void	save_input(t_vars *vars, t_hist *history, t_dlist *entry, char *input)
{
	char	*copy;

	copy = ft_strdup(input);
	if (!copy)
	{
		free(entry);
		clean_exit(vars, errno);
	}
	entry->content = copy;
	ft_dlstadd_front(&history->lst, entry);
}
