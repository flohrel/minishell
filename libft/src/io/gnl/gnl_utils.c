/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:18:57 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:45:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/gnl.h"

int	set_line(t_queue *file_q, char **line)
{
	char	*lptr;
	t_buf	*cur_buf;

	*line = ft_calloc(file_q->len + 1, sizeof(char));
	if (!(*line))
		return (-1);
	lptr = *line;
	cur_buf = file_q->first;
	while (cur_buf)
	{
		ft_memcpy(lptr, cur_buf->data, cur_buf->size);
		lptr += cur_buf->size;
		pop(file_q, 0);
		cur_buf = file_q->first;
	}
	*lptr = '\0';
	file_q = init_file_queue(file_q);
	return (0);
}

t_queue	*init_file_queue(t_queue *file_q)
{
	if (!file_q)
		file_q = ft_calloc(1, sizeof(t_queue));
	if (!file_q)
		return (NULL);
	file_q->len = 0;
	file_q->first = NULL;
	file_q->last = NULL;
	file_q->tmp = NULL;
	return (file_q);
}

int	push(t_queue *file_q, char *buf, size_t size, bool is_tmp)
{
	t_buf	*new_buf;

	new_buf = ft_calloc(1, sizeof(t_buf));
	if (!new_buf)
		return (-1);
	new_buf->data = ft_calloc(size, sizeof(char));
	if (!(new_buf->data))
		return (-1);
	ft_memcpy(new_buf->data, buf, size);
	new_buf->size = size;
	new_buf->next = NULL;
	if (is_tmp == false)
	{
		file_q->len += size;
		if (!(file_q->first))
			file_q->first = new_buf;
		if (file_q->last)
			file_q->last->next = new_buf;
		file_q->last = new_buf;
	}
	else
		file_q->tmp = new_buf;
	return (0);
}

void	pop(t_queue *file_q, bool is_tmp)
{
	t_buf	*cur_buf;

	if (is_tmp == true)
	{
		cur_buf = file_q->tmp;
		file_q->tmp = cur_buf->next;
	}
	else
	{
		cur_buf = file_q->first;
		file_q->len -= cur_buf->size;
		file_q->first = cur_buf->next;
		if (file_q->last == cur_buf)
			file_q->last = NULL;
	}
	free(cur_buf->data);
	free(cur_buf);
}
