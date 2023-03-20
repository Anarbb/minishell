/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:24:25 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/20 21:19:12 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_herd(t_exec *exec)
{
	signal(SIGINT, sig_handl);
	signal(SIGQUIT, sig_handl);
	if (exec->limiter)
		exec->fd_in = open(exec->file_limiter, O_CREAT | O_RDWR, 0777);
	if (fd_error(exec->fd_in, exec->limiter) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

char	*find_exec(t_shell *shell, char *cmd)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*path;
	int				i;

	i = 0;
	while (shell->path[i] && shell->path[i][0] != '\0')
	{
		dirp = opendir(shell->path[i]);
		dp = NULL;
		while (dirp != NULL && get_file_path(&dp, &dirp))
		{
			if (ft_strcmp(dp->d_name, cmd) == 0)
			{
				closedir(dirp);
				path = ft_strjoin(shell->path[i], cmd);
				return (path);
			}
			if (dp == NULL)
				break ;
		}
		i++;
		if (dirp)
			closedir(dirp);
	}
	return (NULL);
}

char	*run_minishell(char *cmd, t_shell *shell)
{
	char	*path;

	path = NULL;
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		path = ft_strdup(cmd);
		return (path);
	}
	else
		path = find_exec(shell, cmd);
	return (path);
}

int	execute(t_shell *shell, t_exec *exec, int j)
{
	pid_t	pid;
	char	*path;

	shell->pid_idx++;
	path = run_minishell(exec->cmd, shell);
	if (open_herd(exec) == FAILURE)
		return (FAILURE);
	pid = fork();
	if (pid == -1)
		return (3);
	shell->pids[shell->pid_idx] = pid;
	if (pid == 0)
	{
		g_sigflag = 0;
		if (find_exec(shell, exec->cmd) != NULL)
		{
			if (exec->fd_in != 0)
				dup2(exec->fd_in, 0);
			dup2(exec->fd_out, 1);
			close_all(shell->pipefd, j - 1, shell->exec);
		}
		if (execute_fbuiltins(exec, shell) == FAILURE)
			execute_command(shell, exec, path);
		exit(EXIT_FAILURE);
	}
	free(path);
	return (g_sigflag = 1, SUCCESS);
}

void	run(t_shell *shell, int j, t_exec *tmp)
{
	tmp = shell->exec;
	if (allocation(shell, &j) == FAILURE)
		return ;
	while (tmp)
	{
		if (tmp->cmd == NULL)
			return ;
		if (execute_builtins(tmp, shell) != SUCCESS)
		{
			if (execute(shell, tmp, j) == 3)
			{
				printf("fork: Resource temporarily unavailable\n");
				return ;
			}
		}
		tmp = tmp->next;
	}
	close_all(shell->pipefd, j - 1, shell->exec);
	while (shell->pid_idx >= 0)
	{
		waitpid(shell->pids[shell->pid_idx], &shell->exit_status, 0);
		exit_status(shell);
		shell->pid_idx--;
	}
}
