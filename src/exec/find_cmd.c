/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:52:04 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/12 11:38:08 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*create_path(char *path, char *cmd, t_vars *vars)
{
	char	*result;

	result = ft_strjoin(path, "/");
	if (!result || !(add_to_ptrlst((void *)result, vars)))
		return (NULL);
	result = ft_strjoin(result, cmd);
	if (!result || !(add_to_ptrlst((void *)result, vars)))
		return (NULL);
	return (result);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
}

int	exec_cmd(char *path, char **argv, char **envp, t_vars *vars)
{
	char		**paths;
	int			i;
	char		*path_x;

	i = 0;
	if (!path || !argv || !envp || !vars)
		return (-1);
	if (ft_ischarset('/', path))
		if (execve(path, argv, envp) < 0)
			printf("bash : %s: No such file or directory.\n", path);
	paths = ft_split(get_env_value("PATH", vars->env), ':');
	if (!paths)
		return (-1);
	while (paths[i])
	{
		path_x = create_path(paths[i], path, vars);
		if (!path_x)
			return (-1);
		if (execve(path_x, argv, envp) < 0)
			i++;
		strerror(errno);
	}
	free_path(paths);
	return (1);
}

int	handle_builtin(char *path, char **argv, t_vars *vars)
{
	vars->last_status = find_builtin(path, argv, vars);
	if (vars->last_status >= 0)
	{
		dup2(vars->cmd.std_in, STDIN_FILENO);
		dup2(vars->cmd.std_out, STDOUT_FILENO);
		close_handle(vars);
		printf("status : %d\n", vars->last_status);
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

	if (handle_builtin(param->path, argv, vars))
		return (1);
	else
		pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		pipe_handle(vars);
		redir_handle(vars, param, &vars->cmd);
		exec_cmd(param->path, tabjoin(param->path, argv, vars),
				envp, vars);
		errormsg(param->path, ": command not found");
		exit(errno);
	}
	close_handle(vars);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		vars->last_status = WEXITSTATUS(status);
	printf("status : %d\n", vars->last_status);
	return (1);
}
