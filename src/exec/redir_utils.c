/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:56:40 by flohrel           #+#    #+#             */
/*   Updated: 2021/07/05 16:46:36 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	delimiter_seek(char *buffer, char *delim, int *i, int *j)
{
	int	ret;

	ret = 1;
	if (buffer[*i] == delim[*j])
	{
		(*j)++;
		if (delim[*j] == '\0')
			ret = 0;
	}
	else
		*j = 0;
	(*i)++;
	return (ret);
}
