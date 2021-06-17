/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:02:16 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/17 19:18:15 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_assign(t_env *block, t_vars *vars)
{
	char	*stack;
	char	*stackb;

	if (ft_endwith(block->key, '+'))
	{
		stack = get_env_value(block->key, vars->agn);
		stackb = block->value;
		block->value = ft_strjoin(stack, block->value);
		free(stack);
		free(stackb);
	}
	add_to_exp(block, vars->agn);
	env_print(vars->agn);
	free(block);
	return (1);
}
