#include "minishell.h"

int	check_fd(t_vars *vars)
{
	pipe_handle(vars);
	close_handle(vars);
	return (1);
}

static int	find_builtin_next(char *path, char **args, t_vars *vars)
{
	if (ft_strcmp("env", path) == 0 && check_fd(vars))
		return (print_env(args, vars));
	else if (ft_strcmp("export", path) == 0 && check_fd(vars))
		return (export(args, vars));
	else if (ft_strcmp("exit", path) == 0 && check_fd(vars))
		return (exit_b(args, vars));
	return (-1);
}

int	find_builtin(char *path, char **args, t_vars *vars)
{
	if (!path || !args || !vars)
		return (-1);
	if (ft_strcmp("echo", path) == 0 && check_fd(vars))
		return (my_echo(args, vars));
	else if (ft_strcmp("cd", path) == 0 && check_fd(vars))
		return (cd(args, vars));
	else if (ft_strcmp("pwd", path) == 0 && check_fd(vars))
		return (pwd(args, vars));
	else if (ft_strcmp("unset", path) == 0 && check_fd(vars))
		return (unset(args, vars));
	return (find_builtin_next(path, args, vars));
}
