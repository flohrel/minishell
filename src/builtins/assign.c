/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:02:16 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/17 20:26:29 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	manage_agn(t_list *assign, t_vars *vars, t_env *block)
{
	char	*stack;
	char	*stackb;
	
	write(1, "de\n", 3);
	(void)assign;
	if (ft_endwith(block->key, '+'))
	{
		write(1, "de\n", 3);
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

int	handle_assign(t_vars *vars, t_list *assign)
{
	t_env	*res;

	while (assign)
	{
		write(1, "de\n", 3);
		res = malloc(sizeof(t_env));
		if (!res)
			return (0);
		write(1, "de\n", 3);
		ft_putstr_fd((char *)(assign->content), 1);
		if (new_envblock((char *)(assign->content), res) == 0)
			return (0);
		write(1, "de\n", 3);
		manage_agn(assign, vars, res);
		free(res);
		assign = assign->next;
	}
	return (1);
}
