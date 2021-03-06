/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:24:24 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/24 17:00:21 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "data.h"
# include "utils.h"
# include "parser.h"
# include "exec.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

t_env	*g_env;

int		find_builtin(char *path, char **args, t_vars *vars, t_param *param);
int		pwd(char **args, t_vars *vars);
int		cd(char **args, t_vars *vars);
int		check_pwd(const char *path, t_vars *vars);
int		cd_end(const char *path, t_vars *vars);
int		exit_b(char **args, t_vars *vars, t_param *param);
int		my_echo(char **args, t_vars *vars);
int		export(char **args, t_vars *vars);
int		init_exp(t_env **env, t_env *elem);
int		print_env(char **args, t_vars *vars);
int		unset(char **args, t_vars *vars);
int		ft_already(char *str, int index, char c);
int		ft_endwith(char *str, char c);
int		ft_startwith(char *str, char c);
int		ft_strischarset(char *str, char *set);
int		ft_ischarset(char c, char *set);
int		ft_tablen(char **args);
int		ft_strisdigit(char *str);
int		errormsg(char *str, char *arg);
int		new_expblock(char *key, char *value, t_env *block);
char	*get_env_value(char *key, t_env *env);
void	print_sorted_env(t_env *env);
void	free_block(t_env *env);
void	free_env(t_env *env);
void	env_print(t_env *env);
void	exp_print(t_env *env);
int		handle_assign_export(t_vars *vars, char **args, t_list *assign);
int		handle_assign(t_vars *vars, t_list *assign);
int		replace_value(t_env *env, t_env *block);
int		add_to_exp(t_env **exp, t_env *block);
int		export_only(char *str, t_env *result, t_vars *vars, int *ret);
t_env	*parse_env(char **env);
t_env	*set_env_value(t_env *env, char *key, char *value);
t_env	*blockcpy(t_env *env);
t_env	*envcpy(t_env *env);
int		new_envblock(char *str, t_env *result);
t_opt	optionhandler(char **args, char *opt, t_vars *vars);
int		failed_path(t_vars *vars, char *path);
int		ret_context(t_env *result);
int		is_pipe(t_io *io);
int		exp_error(char *arg);

#endif
