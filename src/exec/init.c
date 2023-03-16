/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:24:25 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/16 17:17:03 by lsabik           ###   ########.fr       */
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

int	execute_builtins(t_exec *exec, t_shell *shell)
{
	if (exec->fd_in != 0 || exec->fd_out != 1 || exec->next)
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
		else if (ft_strcmp(exec->cmd, "exit") == 0)
			ft_exit(shell);
		else
			return (FAILURE);
		return (SUCCESS);
	}
	else
		printf("halaa\n");
	return (FAILURE);
}

void	execute(t_shell *shell, t_exec *exec, int **pipefd, int j)
{
	pid_t	pid;
	char	*path;

	path = find_exec(shell, exec->cmd);
	if (exec->limiter)
			exec->fd_in = open(g_gvars->limiter_file, O_CREAT | O_RDWR, 0777);
	signal(SIGQUIT, sig_handl);
	signal(SIGINT, sig_handl);
	pid = fork();
	if (pid == -1)
		exit(3);
	if (pid == 0)
	{
		g_gvars->herdoc = 0;
		dup2(exec->fd_in, 0);
		dup2(exec->fd_out, 1);
		close_all(pipefd, j - 1, shell->exec);
		if (execute_builtins(exec, shell) == FAILURE)
			execute_command(shell, exec, path);
		exit(EXIT_FAILURE);
	}
	g_gvars->herdoc = 1;
}

void	run(t_shell *shell)
{
	t_exec	*tmp;
	int		j;
	int		**pipefd;

	tmp = shell->exec;
	j = count_commands(shell->exec);
	pipefd = malloc(sizeof(int) * (j - 1));
	if (!pipefd)
		exit(1);
	pipefd = pipe_handler(shell->exec);
	while (tmp)
	{
		if (tmp->cmd == NULL)
			return ;
		// if (execute_builtins(tmp, shell) == PIPE)
			execute(shell, tmp, pipefd, j);
		tmp = tmp->next;
	}
	close_all(pipefd, j - 1, shell->exec);
	while (wait(NULL) != -1)
		;
}
