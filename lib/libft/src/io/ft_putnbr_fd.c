/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:50:10 by flohrel           #+#    #+#             */
/*   Updated: 2021/01/16 15:55:47 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"

static void	ft_putnbr_fd2(long n, int fd)
{
	if (n > 9)
		ft_putnbr_fd2(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd2(-(long)n, fd);
	}
	else
		ft_putnbr_fd2(n, fd);
}
