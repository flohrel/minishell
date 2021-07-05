/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:23:42 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/05 14:58:24 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include "data.h"
# include "utils.h"
# include "parser.h"

# define TMP_FILE	"/tmp/minish_tmp"

/*
 **		redirections.c
 */
void	parse_redir(t_vars *vars, t_param *param);
void	set_rdout(t_vars *vars, t_cmd *cmd, char *pathname);
void	set_rdapp(t_vars *vars, t_cmd *cmd, char *pathname);
void	set_rdin(t_vars *vars, t_cmd *cmd, char *pathname);
void	set_hdoc(t_vars *vars, t_cmd *cmd, char *string);

/*
 **		redirections2.c
 */


void	exec_ast(t_vars *vars, t_ast *root);
void	*add_to_ptrlst(void *content, t_vars *vars);
int		find_cmd(t_param *param, char **argv, char **envp, t_vars *vars);
char	**tabjoin(char *str, char **args, t_vars *vars);
char	**env_to_tab(t_env *env, t_vars *vars);
int		handle_redirections(t_param *param);
int		env_size(t_env *env);

#endif
