#include "minishell.h"

int	up_shell_lvl(t_vars *vars)
{
	int		lvl;
	char	*lvlstr;
	int		shlvl;
	char	*nb;

	lvl = 0;
	shlvl = 0;
	if (vars->env)
		nb = (get_env_value("SHLVL", vars->env));
	if (nb)
		lvl = ft_atoi(nb);
	if (!lvl)
		lvl = ++shlvl;
	else
		shlvl = ++lvl;
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
