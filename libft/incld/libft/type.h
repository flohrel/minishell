/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:56:49 by flohrel           #+#    #+#             */
/*   Updated: 2021/05/26 17:27:27 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <stdint.h>
# include <stddef.h>
# include <limits.h>

# define TRUE		1
# define FALSE		0

typedef char		t_bool;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

#endif
