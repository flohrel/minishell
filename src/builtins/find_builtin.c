#include "minishell.h"

static int	find_builtin_next(char *path, char **args, t_vars *vars)
{
	if (ft_strcmp("env", path) == 0)
		return (print_env(args, vars));
	else if (ft_strcmp("export", path) == 0)
		return (export(args, vars));
	else if (ft_strcmp("exit", path) == 0)
		return (exit_b(args, vars));
	return (0);
}

int	find_builtin(char *path, char **args, t_vars *vars)
{
	if (!path || !args || !vars)
		return (-1);
	if (ft_strcmp("echo", path) == 0)
		return (my_echo(args, vars));
	else if (ft_strcmp("cd", path) == 0)
		return (cd(args, vars));
	else if (ft_strcmp("pwd", path) == 0)
		return (pwd(args, vars));
	else if (ft_strcmp("unset", path) == 0)
		return (unset(args, vars));
	return (find_builtin_next(path, args, vars));
}
