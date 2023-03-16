/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:24:25 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/16 14:54:20 by aarbaoui         ###   ########.fr       */
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

void	execute_single_cmd(t_exec *tmp, t_shell *shell)
{
	pid_t	pid;
	char	*path;

	path = find_exec(shell, tmp->cmd);
	pid = fork();
	if (pid == -1)
		exit(3);
	if (pid == 0)
	{
		dup2(tmp->fd_in, 0);
		dup2(tmp->fd_out, 1);
		if (tmp->fd_in != 0)
			close(tmp->fd_in);
		if (tmp->fd_out != 1)
			close(tmp->fd_out);
		execute_command(shell, tmp, path);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, 0, 0);
}

void	execute(t_shell *shell, t_exec *exec, int **pipefd, int j)
{
	pid_t	pid;
	char	*path;

	path = find_exec(shell, exec->cmd);
	pid = fork();
	if (pid == -1)
		exit(3);
	if (pid == 0)
	{
		dup2(exec->fd_in, 0);
		dup2(exec->fd_out, 1);
		close_all(pipefd, j - 1, shell->exec);
		execute_command(shell, exec, path);
		exit(EXIT_FAILURE);
	}
	
}

void	run(t_shell *shell)
{
	t_exec	*tmp;
	int		j;
	int		**pipefd;

	j = count_commands(shell->exec);
	if (shell->exec->limiter)
		shell->exec->fd_in = open(g_gvars->limiter_file, O_CREAT | O_RDWR, 0777);
	if (!shell->exec->next)
	{
		execute_single_cmd(shell->exec, shell);
		return ;
	}
	pipefd = malloc(sizeof(int) * (j - 1));
	if (!pipefd)
		exit(1);
	pipefd = pipe_handler(shell->exec);
	tmp = shell->exec;
	while (tmp)
	{
		if (tmp->cmd == NULL)
			return ;
		execute(shell, tmp, pipefd, j);
		tmp = tmp->next;
	}
	close_all(pipefd, j - 1, shell->exec);
	while (wait(NULL) != -1)
		;
}
