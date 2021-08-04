/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:52:04 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/21 03:44:49 by mtogbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_cmd(char *path, char **argv, char **envp, t_vars *vars)
{
	char		**paths;
	int			i;
	char		*path_x;

	i = 0;
	if (!path || !argv || !envp || !vars)
		clean_exit(vars, NULL, errno);
	if (ft_ischarset('/', path))
		exec_absolute_path(path, argv, envp, vars);
	paths = ft_split(get_env_value("PATH", vars->env), ':');
	if (!paths)
		clean_exit(vars, NULL, errno);
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
	exit_status = find_builtin(path, argv, vars, param);
	if (exit_status >= 0)
	{
		dup2(vars->cmd.std_in, STDIN_FILENO);
		dup2(vars->cmd.std_out, STDOUT_FILENO);
		close_handle(vars);
		return (1);
	}
	return (0);
}

void	redir_handle(t_vars *vars, t_param *param, t_cmd *cmd)
{
	parse_redir(vars, param);
	if (check_flag(cmd->io_bit, RD_IN))
		dup2(cmd->redir[FD_IN], FD_IN);
	if (check_flag(cmd->io_bit, RD_OUT))
		dup2(cmd->redir[FD_OUT], FD_OUT);
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
		pipe_handle(vars);
		redir_handle(vars, param, &vars->cmd);
		exec_cmd(param->path, tabjoin(param->path, argv, vars), envp, vars);
		exit(127);
	}
	close_handle(vars);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (1);
}
