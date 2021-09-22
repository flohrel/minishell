/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:52:04 by mtogbe            #+#    #+#             */
/*   Updated: 2021/09/22 17:30:25 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	path_error(char *path, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	return (1);
}

int	exec_cmd(char *path, char **argv, char **envp, t_vars *vars)
{
	char		**paths;
	int			i;
	char		*path_x;

	i = 0;
	if (!path || !argv || !envp || !vars)
		exit(0);
	if (ft_ischarset('/', path))
		exec_absolute_path(path, argv, envp, vars);
	paths = ft_split(get_env_value("PATH", vars->env), ':');
	if (!paths && path_error(path, ": No such file or directory"))
		clean_exit(vars, NULL, NULL, errno);
	while (paths[i])
	{
		path_x = create_path(paths[i], path, vars);
		if (!path_x)
			return (-1);
		if (execve(path_x, argv, envp) < 0)
			i++;
		strerror(errno);
	}
	errormsg(path, ": command not found");
	free_path(paths);
	return (1);
}

int	handle_builtin(char *path, char **argv, t_vars *vars, t_param *param)
{
	g_sig.exit_status = find_builtin(path, argv, vars, param);
	if (g_sig.exit_status >= 0)
	{
		dup2(vars->cmd.std_in, STDIN_FILENO);
		dup2(vars->cmd.std_out, STDOUT_FILENO);
		close_handle(vars);
		return (1);
	}
	return (0);
}

void	parse_cmd(t_vars *vars, t_param *param)
{
	(void)param;
	g_sig.is_child = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	parse_redir(vars, param);
	pipe_handle(vars);
	redir_handle(&vars->cmd);
	clear_pipes(vars);
}

int	find_cmd(t_param *param, char **argv, char **envp, t_vars *vars)
{
	int	pid;
	int	status;

	if (handle_builtin(param->path, argv, vars, param))
		return (1);
	else
		pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		parse_cmd(vars, param);
		exec_cmd(param->path, tabjoin(param->path, argv, vars),
			envp, vars);
		exit (127);
	}
	clear_pipes(vars);
	close_handle(vars);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_sig.exit_status = WEXITSTATUS(status);
	return (1);
}
