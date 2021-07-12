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

#include "builtins.h"

int	pwd(char **args, t_vars *vars)
{
	char	*str;
	char	s[255];
	t_env	*env;

	if (ft_tablen(args))
		return (errormsg("pwd : too many argument", ""));
	env = vars->env;
	str = get_env_value("PWD", env);
	if (!str)
		getcwd(s, 255);
	if (str)
		ft_putstr_fd(str, 1);
	else
		ft_putstr_fd(s, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
