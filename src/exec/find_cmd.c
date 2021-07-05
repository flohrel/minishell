/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtogbe <mtogbe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 14:52:04 by mtogbe            #+#    #+#             */
/*   Updated: 2021/07/01 15:27:35 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "minishell.h"

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
		else
			return (1);
	}
	return (1);
}

void	pipe_handle(t_vars *vars)
{
	if (vars->cmd.io_bit < 0)
		dup2(vars->cmd.pipe[FD_IN], FD_IN);
	else
	{
		if (check_flag(vars->cmd.io_bit, PIPE_IN))
			dup2(vars->cmd.pipe[FD_OUT], FD_OUT);
		if (check_flag(vars->cmd.io_bit, PIPE_OUT))
			dup2(vars->cmd.pipe[FD_IN], FD_IN);
	}
}

void	redir_handle(t_vars *vars, t_cmd *cmd)
{
	parse_redir(vars, vars->param);
	if (check_flag(cmd->io_bit, RD_IN))
		dup2(cmd->redir[FD_IN], FD_IN);
	if (check_flag(cmd->io_bit, RD_OUT))
		dup2(cmd->redir[FD_OUT], FD_OUT);
}

int	find_cmd(t_param *param, char **argv, char **envp, t_vars *vars)
{
	int	pid;
	int	status;

	(void)param;
	(void)argv;
	(void)envp;
	(void)vars;
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		pipe_handle(vars);
		redir_handle(vars, vars->cmd);
		exec_cmd(param->path, tabjoin(param->path, argv, vars),
				envp, vars);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (1);
}
