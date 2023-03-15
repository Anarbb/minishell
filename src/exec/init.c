/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:24:25 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/15 15:18:34 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(t_shell *shell, char *str, int j)
{
	char	*tmp;
	char	*value;
	char	**env;

	env = shell->env_arr;
	if (str[0] == '$')
	{
		j = 1;
		if (ft_isalpha(str[j++]) || str[j++] == '_')
			while (ft_isalnum(str[j]) || str[j] == '_')
				(j)++;
		tmp = ft_strdup(str + 1);
		while (*env != NULL)
		{
			if (ft_strncmp(*env, tmp, j - 1) == 0 && (*env)[j - 1] == '=')
			{
				value = ft_strdup(*env + j);
				return (value);
			}
			env++;
		}
	}
	return (str);
}

void	handle_heredoc(t_shell *shell)
{
	int		fds[2];
	char	*line;

	pipe(fds);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, shell->exec->limiter))
		{
			shell->exec->fd_in = fds[0];
			free(line);
			break ;
		}
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	close(fds[1]);
}

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

void	run(t_shell *shell)
{
	t_exec	*exec;
	pid_t	pid;

	exec = shell->exec;
	while (exec != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (*shell->exec->limiter)
				handle_heredoc(shell);
			if (exec->fd_in != 0)
				dup2(exec->fd_in, 0);
			if (exec->fd_out != 1)
				dup2(exec->fd_out, 1);
			if (execve(find_exec(shell, exec->cmd), exec->args,
					shell->env_arr) == -1)
			{
				printf("hey");
				exit(EXIT_FAILURE);
			}
		}
		waitpid(pid, NULL, 0);
		exec = exec->next;
	}
}
