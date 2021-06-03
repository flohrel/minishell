# include "minishell.h"

int	exit_b(char **args, t_vars *vars)
{
	ft_putstr_fd("exit\n", 1);
	if (args && !(ft_strisdigit(args[0])))
		errormsg("exit : ", "argument numérique nécessaire");
	else if (ft_tablen(args) > 1)
	       return (errormsg("exit : ", "trop d'arguments"));
	if (args && args[0])
		clean_exit(vars, ft_atoi(args[0]));
	else 
		clean_exit(vars, 0);
	return (1);
}
