/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:09:39 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/09 17:09:48 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	exec_ast(t_vars *vars, t_ast *node)
{
	if (!node)
		return ;
	exec_list(vars, node, true);
	close(3);
	close(4);
}
