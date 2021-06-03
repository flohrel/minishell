/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:23:42 by mtogbe            #+#    #+#             */
/*   Updated: 2021/05/31 19:24:32 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "data.h"

int	exec_cmd(t_vars *vars, char **envp);
int	find_cmd(char *path, char **argv, char **envp, t_vars *vars);

#endif
