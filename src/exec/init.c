/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:24:25 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/18 20:24:27 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				path = ft_strjoin(shell->path[i], "/");
				path = ft_strjoin(path, cmd);
				closedir(dirp);
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

int	execute_builtins(t_exec *exec, t_shell *shell)
{
	if (!(exec->fd_in != 0 || exec->fd_out != 1 || exec->next))
	{
		if (ft_strcmp(exec->cmd, "cd") == 0)
			ft_cd(shell, exec);
		else if (ft_strcmp(exec->cmd, "echo") == 0)
			ft_echo(exec);
		else if (ft_strcmp(exec->cmd, "export") == 0)
			ft_export(shell, exec);
		else if (ft_strcmp(exec->cmd, "unset") == 0)
			ft_unset(shell);
		else if (ft_strcmp(exec->cmd, "env") == 0)
			ft_env(shell);
		else if (ft_strcmp(exec->cmd, "pwd") == 0)
			ft_pwd(shell);
		else if (ft_strcmp(exec->cmd, "exit") == 0)
			ft_exit(shell);
		else
			return (FAILURE);
	}
	else
		return (FORK);
	return (SUCCESS);
}

void	execute(t_shell *shell, t_exec *exec, int **pipefd, int j, pid_t **pids,
		int *pid_idx)
{
	pid_t	pid;
	char	*path;

	if (exec->cmd[0] == '/' || exec->cmd[0] == '.')
		path = ft_strdup(exec->cmd);
	else
		path = find_exec(shell, exec->cmd);
	if (exec->limiter)
		exec->fd_in = open(exec->file_limiter, O_CREAT | O_RDWR, 0777);
	if (fd_error(exec->fd_in, exec->limiter) == FAILURE)
			return ;
	signal(SIGINT, sig_handl);
	signal(SIGQUIT, sig_handl);
	pid = fork();
	*pids[*pid_idx++] = pid;
	if (pid == -1)
		exit(3);
	if (pid == 0)
	{
		g_sigflag = 0;
		if (find_exec(shell, exec->cmd) != NULL)
		{
			dup2(exec->fd_in, 0);
			dup2(exec->fd_out, 1);
			close_all(pipefd, j - 1, shell->exec);
		}
		if (execute_Fbuiltins(exec, shell) == FAILURE)
			execute_command(shell, exec, path);
		exit(EXIT_FAILURE);
	}
	g_sigflag = 1;
}

void	run(t_shell *shell)
{
	t_exec	*tmp;
	int		j;
	int		**pipefd;
	pid_t	*pids;
	int		pid_idx;

	tmp = shell->exec;
	j = count_commands(shell->exec);
	pids = (pid_t *)ft_calloc(j, sizeof(pid_t));
	pid_idx = 0;
	pipefd = malloc(sizeof(int) * (j - 1));
	if (!pipefd)
		exit(1);
	pipefd = pipe_handler(shell->exec);
	while (tmp)
	{
		if (tmp->cmd == NULL)
			return ;
		if (execute_builtins(tmp, shell) != SUCCESS)
			execute(shell, tmp, pipefd, j, &pids, &pid_idx);
		tmp = tmp->next;
	}
	close_all(pipefd, j - 1, shell->exec);
	while (pid_idx >= 0)
	{
		waitpid(pids[pid_idx], &shell->exit_status, 0);
		if (!WIFSIGNALED(shell->exit_status))
				shell->exit_status = WEXITSTATUS(shell->exit_status);
			else
				shell->exit_status = 128 + WTERMSIG(shell->exit_status);
		pid_idx--;
	}
}
