/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:42:38 by flohrel           #+#    #+#             */
/*   Updated: 2021/04/28 19:21:19 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	display_prompt(void)
{
	write(1, PROMPT, ft_strlen(PROMPT));
}

/*int		input_handle(char *input, int size)
{
	if (size == 4)
	{

	}
}*/

void	ft_readline(t_vars *vars)
{
	char	buffer[BUFFER_SIZE];
	int		size;
//	int		ret;
	int		i;

	size = 0;
	i = 0;
//	ret = -1;
//	while (ret)
//	{
		size = read(0, &buffer[i], 4);
		printf("size = %d\n", size);
		if (size == -1)
			clean_exit(vars, errno);
//		ret = input_handle(&buffer[i], size);
		i += 4;
//	}
	vars->lexer.buffer = ft_calloc(i + 1, sizeof(*(vars->lexer.buffer)));
	if (vars->lexer.buffer == NULL)
		clean_exit(vars, errno);
	ft_strlcpy(vars->lexer.buffer, buffer, i + 1);
}
