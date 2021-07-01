#include "minishell.h"

int	up_shell_lvl(t_vars *vars)
{
	int	lvl;

	lvl = ft_atoi(get_env_value("SHLVL", vars->env)) + 1;
	vars->env = set_env_value(vars->env, "SHLVL", ft_itoa(lvl));
	vars->exp = set_env_value(vars->exp, "SHLVL", ft_itoa(lvl));
	return (1);
}
