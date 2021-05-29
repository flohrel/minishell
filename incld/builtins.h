/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:24:24 by mtogbe            #+#    #+#             */
/*   Updated: 2021/05/29 18:54:46 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env	*g_env;

int 	pwd(t_env *env);
int		cd(const char *path);
int		echo(int fd, char **tab, int opt);
int		export(char *str, t_env *env);
char	*get_env_value(char *key, t_env *env);
void	print_env(t_env *env);
void	print_sorted_env(t_env *env);
void	free_block(t_env *env);
void	free_env(t_env *env);
t_env	*blockcpy(t_env *env);
t_env	*envcpy(t_env *env);
t_env	*unset(char *key, t_env *env);
t_env	*new_envblock(char *str)
#endif
