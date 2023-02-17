/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/17 14:44:46 by lsabik           ###   ########.fr       */
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
	while (shell->path[i])
	{
		dirp = opendir(shell->path[i]);
		while ((dp = readdir(dirp)) != NULL)
		{
			if (ft_strcmp(dp->d_name, cmd) == 0)
			{
				path = ft_strjoin(shell->path[i], "/");
				path = ft_strjoin(path, dp->d_name);
				closedir(dirp);
				return (path);
			}
		}
		i++;
		closedir(dirp);
	}
	return (NULL);
}

void	exec_cmd(t_shell *shell, char *path)
{
	pid_t pid;
	int status;

	// hadi tr9i3a to run local executables pls dont use :D
	if (path == NULL)
		path = shell->cmd[0];
	if (ft_strcmp(shell->cmd[0], "exit") == 0)
		exit_cmd(shell, shell->cmd[1]);
	else if (ft_strcmp(shell->cmd[0], "cd") == 0)
		ft_cd(shell);
	else if (shell->cmd[0][0] == '$')
		expander(shell, shell->cmd[0]);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, &shell->cmd[0], shell->env) == -1)
			{
				ft_putstr_fd("minishell: command not found: ", 2);
				ft_putendl_fd(shell->cmd[0], 2);
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
}