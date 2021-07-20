#include "minishell.h"

int	up_shell_lvl(t_vars *vars)
{
	int		lvl;
	char		*lvlstr;
	static int	shlvl = 0;

	lvl = 0;
	if (vars->env)
		lvl = ft_atoi(get_env_value("SHLVL", vars->env)) + 1;
	if (!lvl)
		lvl = ++shlvl;
	else
		shlvl = lvl;
	lvlstr = ft_itoa(lvl);
	vars->env = set_env_value(vars->env, "SHLVL", lvlstr);
	if (!vars->env)
		clean_exit(vars, NULL, errno);
	vars->exp = set_env_value(vars->exp, "SHLVL", lvlstr);
	if (!vars->exp)	
		clean_exit(vars, NULL, errno);
	free(lvlstr);
	return (1);
}
