/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:56:49 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:22:00 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_list	t_list;
typedef struct s_dlist	t_dlist;

struct s_list
{
	void	*content;
	t_list	*next;
};

struct s_dlist
{
	void	*content;
	t_dlist	*prev;
	t_dlist	*next;
};

#endif
