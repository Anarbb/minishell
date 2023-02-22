/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/22 15:41:06 by aarbaoui         ###   ########.fr       */
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
	pid_t pid;
	int status;

	// hadi tr9i3a to run local executables pls dont use :D
	if (path == NULL)
		path = shell->cmd[0];
	if (ft_strcmp(shell->cmd[0], "exit") == 0)
		exit_cmd(shell, shell->cmd[1]);
	else if (ft_strcmp(shell->cmd[0], "cd") == 0)
		ft_cd(shell);
	else if (ft_strcmp(shell->cmd[0], "export") == 0)
	{
		if (shell->cmd[1] == NULL || shell->cmd[2] == NULL)
			ft_export(shell, NULL, NULL);
		else
			ft_export(shell, shell->cmd[1], shell->cmd[2]);
	}
	else if (ft_strcmp(shell->cmd[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(shell->cmd[0], "unset") == 0)
	{
		if (shell->cmd[1] == NULL)
			ft_putendl_fd("unset: not enough arguments", 2);
		else
			ft_unset(shell, shell->cmd[1]);
	}
	// else if (shell->cmd[0][0] == '$')
	// 	expander(shell, shell->cmd[0]);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, &shell->cmd[0], shell->tmp_env) == -1)
			{
				ft_putstr_fd("minishell: command not found: ", 2);
				ft_putendl_fd(shell->cmd[0], 2);
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	set_env(shell, "_", shell->cmd[0]);
}