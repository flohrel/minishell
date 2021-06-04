/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:23:42 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/03 18:02:26 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data.h"

void	exec_ast(t_vars *vars, t_ast *root);
void	*add_to_ptrlst(void *content, t_vars *vars);
int	find_cmd(char *path, char **argv, char **envp, t_vars *vars);
char	**tabjoin(char *str, char **args, t_vars *vars);
char	**env_to_tab(t_env *env, t_vars *vars);
int	env_size(t_env *env);

#endif
