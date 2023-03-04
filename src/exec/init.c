/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/04 17:02:16 by aarbaoui         ###   ########.fr       */
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
		path = shell->exec->bin;
	pid = fork();
	if (pid == 0)
	{
		if (exec->fd_in != 0)
			dup2(exec->fd_in, 0);
		if (exec->fd_out != 1)
			dup2(exec->fd_out, 1);
		if (execve(path, exec->args, shell->env_arr) == -1)
		{
			printf("minishell: %s: command not found\n", exec->args[0]);
			exit(1);
		}
		close(exec->fd_in);
		close(exec->fd_out);
	}
	else
		waitpid(pid, &status, 0);
}

void	run(t_shell *shell)
{
	if (ft_strcmp(shell->exec->bin, "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->exec->bin, "cd") == 0)
		ft_cd(shell);
	else if (ft_strcmp(shell->exec->bin, "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(shell->exec->bin, "unset") == 0)
		ft_unset(shell);
	else if (ft_strcmp(shell->exec->bin, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(shell->exec->bin, "exit") == 0)
		ft_exit(shell);
	else
	{
		shell->exec->bin = find_exec(shell, shell->exec->bin);
		exec_cmd(shell, shell->exec->bin);
	}
}
