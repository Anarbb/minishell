/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/02 20:42:03 by lsabik           ###   ########.fr       */
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
	if (pid == 0 && shell->exec->fd_in > 0)
	{
		dup2(shell->exec->fd_in, 0);
		dup2(shell->exec->fd_out, 1);
		if (shell->exec->fd_in != 0)
			close(shell->exec->fd_in);
		// printf("path: %s", path);
		// while (cmd)
		// {
		// 	printf("%s\n", *cmd);
		// 	cmd++;
		// }
		// printf("%s\n",shell->exec->args[0]);
		if (execve(path, shell->exec->args, shell->tmp_env) == -1)
		{
			ft_putstr_fd("minishell: command not found: \n", 2);
			// ft_putendl_fd(cmd[0], 2);
			exit(127);
		}
	}
	else
		waitpid(pid, &status, 0);
	
}
