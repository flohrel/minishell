/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 19:23:42 by mtogbe            #+#    #+#             */
/*   Updated: 2021/10/19 19:29:05 by flohrel          ###   ########.fr       */
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

void	sigquit_handler(int signum);
/*
 **		redir0.c
 */
int		parse_redir(t_vars *vars, t_param *param);
int		set_rdout(t_io *io, char *pathname);
int		set_rdapp(t_io *io, char *pathname);
int		set_rdin(t_io *io, char *pathname);
int		set_hdoc(t_vars *vars, t_io *io, char *string, bool hax_exp);

/*
 **		redir1.c
 */
void	redir_handle(t_io *io);
int		close_redir(t_io *io);
void	hdoc_copy(t_vars *vars, char **buf, char *str, bool has_exp);
int		parse_redir2(t_vars *vars, t_param *param, t_token *token);
int		redir_error(char *arg);

/*
 **		exec0.c
 */
void	exec_ast(t_vars *vars, t_ast *node);
int		exec_list(t_vars *vars, t_ast *node, bool is_exec);
int		exec_list2(t_vars *vars, t_ast *node, bool is_exec);

/*
 **		exec1.c
 */
void	exec_sub(t_vars *vars, t_ast *node);
int		exec_job(t_vars *vars, t_ast *node);
void	fork_pipeline(t_vars *vars, t_ast *node);
void	exec_pipeline(t_vars *vars, t_ast *node, int ct);
void	exec_command(t_vars *vars, t_ast *node);

/*
 **		pipes.c
 */
pid_t	exec_last_pipe(t_vars *vars, t_ast *node);
void	exec_first_pipe(t_io *io);
void	clear_pipes(t_vars *vars, t_io *io);
int		pipe_handle(t_io *io);
int		close_handle(t_vars *vars, t_param *param);

/*
 **		find_cmd.c
 */
int		path_error(char *path, char *msg);
int		exec_cmd(char *path, char **argv, char **envp, t_vars *vars);
int		handle_builtin(char *path, char **argv, t_vars *vars, t_param *param);
void	parse_cmd(t_vars *vars, t_param *param);
int		find_cmd(t_param *param, char **argv, char **envp, t_vars *vars);

char	**tabjoin(char *str, char **args, t_vars *vars);
char	**env_to_tab(t_env *env, t_vars *vars);
int		handle_redirections(t_param *param);
int		env_size(t_env *env);
int		add_pipe(t_vars *vars, t_ast *node);
char	*create_path(char *path, char *cmd, t_vars *vars);
void	free_path(char **path);
void	exec_absolute_path(char *path, char **argv, char **envp, t_vars *vars);

#endif
