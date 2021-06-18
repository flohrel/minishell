/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:02:16 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/18 15:48:51 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	manage_agn(t_list *assign, t_vars *vars, t_env *block)
{
	char	*stack;
	char	*stackb;
	
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
	if (!vars->agn)
		vars->agn = block;
	else
		add_to_exp(vars->agn, block);
	env_print(vars->agn);
	return (1);
}

int	handle_assign(t_vars *vars, t_list *assign)
{
	t_env	*res;

	while (assign)
	{
		res = malloc(sizeof(t_env));
		if (!res)
			return (0);
		if (new_envblock(((t_token *)(assign->content))->data, res) == 0)
			return (0);
		exp_print(res);
		manage_agn(assign, vars, res);
		free(res);
		assign = assign->next;
	}
	env_print(vars->agn);
	return (1);
}
