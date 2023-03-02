/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/02 13:37:24 by aarbaoui         ###   ########.fr       */
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
		printf("path: %s", path);
		// while (cmd)
		// {
		// 	printf("%s\n", *cmd);
		// 	cmd++;
		// }
		// if (execve(path, opt, shell->tmp_env) == -1)
		// {
		// 	ft_putstr_fd("minishell: command not found: \n", 2);
		// 	ft_putendl_fd(cmd[0], 2);
		// 	exit(127);
		// }
	}
	else
		waitpid(pid, &status, 0);
	
}
