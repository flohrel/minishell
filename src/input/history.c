/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:02:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 02:31:11 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*void	hist_import(t_vars *vars)
{
}

void	hist_export(t_vars *vars)
{
}*/

void	save_input(t_vars *vars, char *input)
{
	t_dlist	*lst;
	t_hist	*hist;
	char	*copy;

	copy = ft_strdup(input);
	if (!copy)
		clean_exit(vars, errno);
	hist = ft_calloc(1, sizeof(*hist));
	if (!hist)
	{
		free(copy);
		clean_exit(vars, errno);
	}
	hist->input = copy;
	lst = ft_dlstnew(hist);
	if (!lst)
	{
		free(copy);
		free(hist);
		clean_exit(vars, errno);
	}
	ft_dlstadd_front(&vars->history, lst);
}
