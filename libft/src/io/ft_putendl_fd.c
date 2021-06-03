/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:44:39 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:55:54 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

size_t	ft_putendl_fd(char *s, int fd)
{
	size_t	nbyte;

	if (!s)
		return (0);
	nbyte = ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return (nbyte + 1);
}
