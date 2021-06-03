/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:44:07 by mtogbe            #+#    #+#             */
/*   Updated: 2021/06/02 19:40:05 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(char **args, t_vars *vars)
{
	char	*str;
	t_env	*env;

	if (ft_tablen(args))
		return (errormsg("pwd : too many argument", ""));
	env = vars->env;
	str = get_env_value("PWD", env);
	if (!str)
		str = get_env_value("OLDPWD", env);
	if (!str)
		return (-1);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	return (1);
}
