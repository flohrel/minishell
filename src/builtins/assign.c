/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:02:16 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/20 16:49:47 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	assign_add(t_env *block, t_vars *vars)
{
	char	*stack;
	char	*stackb;

	(block->key)[ft_strlen(block->key) - 2] = '\0';
	//chercher egalement la valeur dans la list export
	stack = get_env_value(block->key, vars->exp);
	if (!stack)
		stack = get_env_value(block->key, vars->agn);
	if (!stack)
		stack = ft_strdup("\0");
	stackb = block->value;
	block->value = ft_strjoin(stack, block->value);
	if (!(block->value))
			return (-1);
	free(stackb);
	return (1);
}

int	manage_agn(t_list *assign, t_vars *vars, t_env *block)
{
	(void)assign;
	if (ft_endwith(block->key, '+'))
		if (assign_add(block, vars) < 0)
			return (-1);
	if (get_env_value(block->key, vars->env))
		if (add_to_exp(vars->env, block) < 0)
			return (-1);
	if (get_env_value(block->key, vars->exp))
		if (add_to_exp(vars->exp, block) < 0)
			return (-1);
	if (!vars->agn)
		vars->agn = blockcpy(block);
	else
		if (add_to_exp(vars->agn, block) < 0)
			return (-1);
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
