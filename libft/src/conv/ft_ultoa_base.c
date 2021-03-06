/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:50:37 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/10 13:26:32 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/conv.h"

static int	ft_isvalid(char *base)
{
	char	*ptr;

	if (!base)
		return (0);
	while (*base)
	{
		if ((*base == '+') || (*base == '-') || (*base < 33) || (*base > 126))
			return (0);
		ptr = base + 1;
		while (*ptr)
		{
			if (*ptr == *base)
				return (0);
			ptr++;
		}
		base++;
	}
	return (1);
}

static size_t	str_alloc(unsigned long n, char **str, size_t base_len)
{
	size_t			str_len;

	str_len = 0;
	while (n)
	{
		str_len++;
		n /= base_len;
	}
	if (!str_len)
		str_len++;
	*str = ft_calloc(str_len + 1, sizeof(char));
	*(*str + str_len) = '\0';
	return (str_len);
}

static void	base_convert(unsigned long n, char *str, char *base,
		size_t base_len)
{
	if (n >= base_len)
		base_convert(n / base_len, str - 1, base, base_len);
	*str = base[n % base_len];
}

char	*ft_ultoa_base(unsigned long n, char *base)
{
	size_t			str_len;
	size_t			base_len;
	char			*str;

	base_len = ft_strlen(base);
	if (!ft_isvalid(base)
		|| base_len < 2)
		return (NULL);
	str = NULL;
	str_len = str_alloc(n, &str, base_len);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = base[0];
	base_convert(n, &str[str_len - 1], base, base_len);
	return (str);
}
