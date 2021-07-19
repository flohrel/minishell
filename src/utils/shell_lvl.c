#include "minishell.h"

int	up_shell_lvl(t_vars *vars)
{
	int	lvl;
	char	*lvlstr;

	lvl = ft_atoi(get_env_value("SHLVL", vars->env)) + 1;
	lvlstr = ft_itoa(lvl);
	vars->env = set_env_value(vars->env, "SHLVL", lvlstr);
	vars->exp = set_env_value(vars->exp, "SHLVL", lvlstr);
	free(lvlstr);
	return (1);
}
