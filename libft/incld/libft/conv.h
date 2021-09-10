/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:32:40 by flohrel           #+#    #+#             */
/*   Updated: 2021/09/10 13:23:47 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONV_H
# define CONV_H

# include "type.h"
# include "ctype.h"
# include "memory.h"

int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
char			*ft_ltoa(int64_t n);
char			*ft_ltoa_base(int64_t n, char *base);
char			*ft_ultoa_base(uint64_t n, char *base);
char			*ft_uint_to_utf8(const uint32_t c);

#endif
