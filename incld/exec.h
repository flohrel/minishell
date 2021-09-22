/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:23:42 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/22 14:29:23 by mtogbe           ###   ########.fr       */
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
# include "input.h"

# define TMP_FILE	"/tmp/minish-hdoc"

/*
 **		redirection.c
 */
void	parse_redir(t_vars *vars, t_param *param);
void	set_rdout(t_vars *vars, t_cmd *cmd, char *pathname);
void	set_rdapp(t_vars *vars, t_cmd *cmd, char *pathname);
void	set_rdin(t_vars *vars, t_cmd *cmd, char *pathname);
void	set_hdoc(t_vars *vars, t_cmd *cmd, char *string, bool hax_exp);

/*
 **		exec0.c
 */
void	exec_ast(t_vars *vars, t_ast *node);
void	exec_list(t_vars *vars, t_ast *node, bool is_exec);
void	exec_list2(t_vars *vars, t_ast *node, bool is_exec);

/*
 **		exec1.c
 */
void	exec_sub(t_vars *vars, t_ast *node);
void	exec_job(t_vars *vars, t_ast *node);
void	exec_pipeline(t_vars *vars, t_cmd *cmd, t_ast *node, int ct);
void	exec_command(t_vars *vars, t_ast *node);

/*
 **		find_cmd.c
 */
int		path_error(char *path, char *msg);
void	sigint_handler(int signum);
void	redir_handle(t_cmd *cmd);

int		find_cmd(t_param *param, char **argv, char **envp, t_vars *vars);
char	**tabjoin(char *str, char **args, t_vars *vars);
char	**env_to_tab(t_env *env, t_vars *vars);
int		handle_redirections(t_param *param);
int		env_size(t_env *env);
int		add_pipe(t_vars *vars, t_ast *node);
int		pipe_handle(t_vars *vars);
int		close_handle(t_vars *vars);
char	*create_path(char *path, char *cmd, t_vars *vars);
void	free_path(char **path);
void	exec_absolute_path(char *path, char **argv, char **envp, t_vars *vars);
pid_t	exec_last_pipe(t_vars *vars, t_cmd *cmd, t_ast *node);
void	exec_first_pipe(t_vars *vars, t_cmd *cmd, t_ast *node);
void	clear_pipes(t_vars *vars);

#endif
