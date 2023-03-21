/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:53:34 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/21 12:05:30 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_exec *exec)
{
	int	count;

	count = 0;
	while (exec)
	{
		count++;
		exec = exec->next;
	}
	return (count);
}

int	execute_fbuiltins(t_exec *exec, t_shell *shell)
{
	if (ft_strcmp(exec->cmd, "cd") == 0)
		ft_cd(shell, exec, NULL, NULL);
	else if (ft_strcmp(exec->cmd, "echo") == 0)
		ft_echo(exec, 1, 1);
	else if (ft_strcmp(exec->cmd, "export") == 0)
		ft_export(shell, exec, 0, 1);
	else if (ft_strcmp(exec->cmd, "unset") == 0)
		ft_unset(shell);
	else if (ft_strcmp(exec->cmd, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(exec->cmd, "exit") == 0)
		ft_exit(shell, 0);
	else
		return (FAILURE);
	return (SUCCESS);
}

void	exit_status(t_shell *shell)
{
	if (!WIFSIGNALED(shell->exit_status))
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	else
		shell->exit_status = 128 + WTERMSIG(shell->exit_status);
}

int	execute_builtins(t_exec *exec, t_shell *shell)
{
	if (!(exec->fd_in != 0 || exec->fd_out != 1 || exec->next))
	{
		if (ft_strcmp(exec->cmd, "cd") == 0)
			ft_cd(shell, exec, NULL, NULL);
		else if (ft_strcmp(exec->cmd, "echo") == 0)
			ft_echo(exec, 1, 1);
		else if (ft_strcmp(exec->cmd, "export") == 0)
			ft_export(shell, exec, 0, 1);
		else if (ft_strcmp(exec->cmd, "unset") == 0)
			ft_unset(shell);
		else if (ft_strcmp(exec->cmd, "env") == 0)
			ft_env(shell);
		else if (ft_strcmp(exec->cmd, "pwd") == 0)
			ft_pwd(shell);
		else if (ft_strcmp(exec->cmd, "exit") == 0)
			ft_exit(shell, 0);
		else
			return (FAILURE);
	}
	else
		return (FORK);
	return (SUCCESS);
}

int	allocation(t_shell *shell, int *j)
{
	*j = count_commands(shell->exec);
	shell->pipefd = NULL;
	if (!shell->pids)
		shell->pids = (pid_t *)ft_calloc(*j + 1, sizeof(pid_t));
	shell->pid_idx = -1;
	if (*j > 1)
		shell->pipefd = pipe_handler(shell->exec);
	return (SUCCESS);
}
