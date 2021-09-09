/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:23:52 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/09 17:25:19 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	replace_cpy(char *dst, char **replace, int i)
{
	int	j;
	int	k;

	j = 0;
	while (replace[j])
	{
		k = 0;
		while (replace[j][k])
			dst[i++] = replace[j][k++];
		if (replace[j + 1])
			dst[i++] = ' ';
		j++;
	}
	dst[i] = '\0';
}

char	*ft_replace(char *dst, char **replace)
{
	int	i;

	i = 0;
	dst[i] = '\0';
	replace_cpy(dst, replace, i);
	return (dst);
}
