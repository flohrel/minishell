#include "minishell.h"

static int	find_builtin_next(char *path, char **args, t_vars *vars)
{
	if (ft_strcmp("env", path) == 0)
	{
		print_env(args, vars);
	}
	else if (ft_strcmp("export", path) == 0)
	{
		write(1,"o",1);
		if (export(args, vars) < 0)
			return (-1);
	}
	else if (ft_strcmp("exit", path) == 0)
	{
		exit_b(args, vars);
	}
	return (1);
}

int	find_builtin(char *path, char **args, t_vars *vars)
{
	if (ft_strcmp("echo", path) == 0)
	{
		if (my_echo(args, vars) < 0)
			return (-1);
	}
	else if (ft_strcmp("cd", path) == 0)
	{
		if (cd(args, vars) < 0)
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
	find_builtin_next(path, args, vars);
	return (1);
}
