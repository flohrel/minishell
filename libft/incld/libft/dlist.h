/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 14:34:45 by flohrel           #+#    #+#             */
/*   Updated: 2021/06/04 01:16:38 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H

# include "type.h"
# include "memory.h"

t_dlist			*ft_dlstnew(void *content);
void			ft_dlstadd_front(t_dlist **alst, t_dlist *new);
int				ft_dlstsize(t_dlist *lst);
t_dlist			*ft_dlstlast(t_dlist *lst);
void			ft_dlstadd_back(t_dlist **alst, t_dlist *new);
void			ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void			ft_dlstclear(t_dlist **lst, void (*del)(void *));
void			ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist			*ft_dlstmap(t_dlist *lst, void *(*f)(void *), \
		void (*del)(void *));

#endif
