/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:24:25 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/15 23:34:09 by lsabik           ###   ########.fr       */
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
	waitpid(-1, 0, 0);
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
		close_all(pipefd, j - 1, exec);
		execute_command(shell, exec, path);
		exit(EXIT_FAILURE);
	}
}

void	run(t_shell *shell)
{
	t_exec	*tmp;
	int		j;
	int		**pipefd;

	tmp = shell->exec;
	j = count_commands(tmp);
	if (tmp->limiter)
		tmp->fd_in = open(g_gvars->limiter_file, O_CREAT | O_RDWR, 0777);
	if (!tmp->next)
	{
		execute_single_cmd(tmp, shell);
		return ;
	}
	pipefd = malloc(sizeof(int) * (j - 1));
	if (!pipefd)
		exit(1);
	pipefd = pipe_handler(tmp);
	while (tmp)
	{
		if (tmp->cmd == NULL)
			return ;
		execute(shell, tmp, pipefd, j);
		tmp = tmp->next;
	}
	close_all(pipefd, j - 1, tmp);
	while (wait(NULL) != -1)
		;
}
