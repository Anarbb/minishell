/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/05 18:58:18 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_exec(t_shell *shell, char *cmd)
{
	DIR *dirp;
	struct dirent *dp;
	char *path;
	int i;
	
	i = 0;
	while (shell->path[i] && shell->path[i][0] != '\0')
	{
		dirp = opendir(shell->path[i]);
		while (dirp && (dp = readdir(dirp)) != NULL)
		{
			if (ft_strcmp(dp->d_name, cmd) == 0)
			{
				path = ft_strjoin(shell->path[i], "/");
				path = ft_strjoin(path, cmd);
				closedir(dirp);
				return (path);
			}
		}
		i++;
		if (dirp)
			closedir(dirp);
	}
	return (NULL);
}


void	exec_cmd(t_shell *shell, char *path)
{
	pid_t	pid;
	t_exec	*exec;
	int		status;

	exec = shell->exec;	
	if (path == NULL)
		path = shell->exec->cmd;
		
	pid = fork();
	if (pid == 0)
	{
		if (exec->fd_in != 0)
			dup2(exec->fd_in, 0);
		if (exec->fd_out != 1)
			dup2(exec->fd_out, 1);
		dup2(exec->fd_in, 0);
		if (execve(path, exec->args, shell->tmp_env) == -1)
		{
			printf("minishell: %s: command not found\n", exec->cmd);
			shell->exit_status = 127;
			exit(EXIT_FAILURE);
		}
		close(exec->fd_in);
		close(exec->fd_out);
		unlink(limiter_path(exec->limiter));
	}
	else
		waitpid(pid, &status, 0);
}
void	handle_heredoc(t_shell *shell, t_exec *exec)
{
	char	*line;
	(void)shell;

	while (exec->herdoc == 1)
	{
		line = readline("> ");
		if (ft_strcmp(line, exec->limiter) == 0)
		{
			// free(line);
			write(1, "\n", 1);
			return ;
		}
		write(exec->fd_in, line, ft_strlen(line));
		write(exec->fd_in, "\n", 1);
	}
}

void	run(t_shell *shell)
{
	if (ft_strcmp(shell->exec->cmd, "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->exec->cmd, "cd") == 0)
		ft_cd(shell);
	else if (ft_strcmp(shell->exec->cmd, "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(shell->exec->cmd, "unset") == 0)
		ft_unset(shell);
	else if (ft_strcmp(shell->exec->cmd, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(shell->exec->cmd, "exit") == 0)
		ft_exit(shell);
	else
    {
		if (shell->exec->herdoc == 1)
			handle_heredoc(shell, shell->exec);
        shell->exec->cmd = find_exec(shell, shell->exec->cmd);
        exec_cmd(shell, shell->exec->cmd);
    }
}