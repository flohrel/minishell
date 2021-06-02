/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:24:24 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/01 15:13:27 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "data.h"
# include <dirent.h>
# include <sys/types.h>

t_env	*g_env;

int		find_builtin(char *path, char **args, t_vars *vars);
int		pwd(char **args, t_vars *vars);
int		cd(char **args, t_vars *vars);
int		my_echo(char **args, t_vars *vars);
int		export(char **args, t_vars *vars);
int		print_env(char **args, t_vars *vars);
int		unset(char **args, t_vars *vars);
int		ft_already(char *str, int index, char c);
int		ft_endwith(char *str, char c);
int		ft_startwith(char *str, char c);
int		ft_ischarset(char c, char *set);
int		ft_tablen(char **args);
int		errormsg(char *str, char *arg);
char	*get_env_value(char *key, t_env *env);
void	print_sorted_env(t_env *env);
void	free_block(t_env *env);
void	free_env(t_env *env);
t_env	*parse_env(char **env, t_vars *vars);
t_env	*blockcpy(t_env *env);
t_env	*envcpy(t_env *env);
t_env	*new_envblock(char *str, t_env *result, t_vars *vars);
t_opt	optionhandler(char **args, char *opt, t_vars *vars);

#endif
