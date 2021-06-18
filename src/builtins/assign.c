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
		write(1, "de\n", 3);
		(block->key)[ft_strlen(block->key) - 2] = '\0';
		//chercher egalement la valeur dans la list export
		stack = get_env_value(block->key, vars->agn);
		if (!stack)
			stack = ft_strdup("");
		stackb = block->value;
		block->value = ft_strjoin(stack, block->value);
//		pourauoi ca free un truc pas alloue
//		free(stack);
//		free(stackb);
	}
	if (!vars->agn)
		vars->agn = blockcpy(block);
	else
		add_to_exp(vars->agn, block);
	return (1);
}

int	handle_assign(t_vars *vars, t_list *assign)
{
	t_env	*res;

	env_print(vars->agn);
	while (assign)
	{
		res = malloc(sizeof(t_env));
		if (!res)
			return (0);
		if (new_envblock(((t_token *)(assign->content))->data, res) == 0)
			return (0);
		manage_agn(assign, vars, res);
		free(res);
		assign = assign->next;
	}
	env_print(vars->agn);
	return (1);
}
