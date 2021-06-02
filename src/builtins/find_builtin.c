#include "minishell.h"

/*static int	find_builtin_next(char *path, char **args, t_vars *vars)
{
	if (ft_strcmp("env", path))
	{
		print_env(args, vars->env);
	}
	else if (ft_strcmp("exit", path))
	{
		clean_exit(etc);
	}
}*/

int	find_builtin(char *path, char **args, t_vars *vars)
{
	if (ft_strcmp("echo", path) == 0)
	{
		if (my_echo(args, vars) < 0)
			return (-1);
	}
	else if (ft_strcmp("cd", path) == 0)
	{
		if (cd((const char **)args) < 0)
			return (-1);
	}
	else if (ft_strcmp("pwd", path) == 0)
	{
		if (pwd(args, vars) < 0)
			return (-1);
	}
	else if (ft_strcmp("unset", path) == 0)
	{
		if (unset(args, vars) < 0)
			return (-1);
	}
	//find_builtin_next(path, args, vars);
	return (1);
}
