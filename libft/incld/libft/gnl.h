/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:18:14 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/26 18:53:24 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "type.h"
# include "memory.h"
# include "string.h"

# ifndef GNL_BUF_SIZE
#  define GNL_BUF_SIZE	4096
# endif

# define MAX_FD			1024

typedef struct	s_buf
{
	size_t			size;
	char			*data;
	struct s_buf	*next;
}				t_buf;

typedef struct	s_queue
{
	size_t	len;
	t_buf	*tmp;
	t_buf	*first;
	t_buf	*last;
}				t_queue;

int				get_next_line(int fd, char **line);
int				set_line(t_queue *file_q, char **line);
t_queue			*init_file_queue(t_queue *file_q);
int				push(t_queue *file_q, char *buf, size_t size, t_bool is_tmp);
void			pop(t_queue *file_q, t_bool is_tmp);

#endif
