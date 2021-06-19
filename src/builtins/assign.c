/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:02:16 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/18 17:11:08 by mtogbe           ###   ########.fr       */
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
		write(1, "add\n", 4);
		(block->key)[ft_strlen(block->key) - 2] = '\0';
		//chercher egalement la valeur dans la list export
		stack = get_env_value(block->key, vars->env);
		if (!stack)
			stack = get_env_value(block->key, vars->agn);
		if (!stack)
			stack = ft_strdup("\0");
		stackb = block->value;
		block->value = ft_strjoin(stack, block->value);
		if (!(block->value))
				return (-1);
		free(stackb);
	}
	if (!vars->agn)
		vars->agn = blockcpy(block);
	else
		if (add_to_exp(vars->agn, block) < 0)
			return (-1);
	env_print(vars->agn);
	env_print(block);
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
		manage_agn(assign, vars, res);
		free_block(res);
		assign = assign->next;
	}
	env_print(vars->agn);
	return (1);
}
