/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/14 21:45:03 by lsabik           ###   ########.fr       */
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

void	handle_heredoc(t_shell *shell, t_exec *exec, int fd)
{
	char	*line;
	// pid_t	pid;

	while (1)
	{
		gvars->herdoc = 0;
		line = readline("> ");
		signal(SIGINT, SIG_DFL);
		if (line == NULL)
			return ;
		if (gvars->inside_quotes == WITHOUT_QUOTES)
			line = expand_heredoc(shell, line, 0);
		if (ft_strcmp(line, exec->limiter) == 0)
		{
			free(line);
			return ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
	}
	exec->fd_in = fd;
	dup2(exec->fd_in, 0);
	close(0);
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


void close_all(int *fd, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        close(fd[i]);
        i++;
    }
}
int	count_cmmds(t_exec *exec)
{
	t_exec *tmp;
	int count;

	count = 0;
	tmp = exec;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return(count);
}


void execute_command(t_shell *shell, t_exec *exec, char *path)
{
	if (execve(path, exec->args, shell->env_arr) == -1)
	{
		printf("minishell: %s: command not found\n", exec->args[0]);
		shell->exit_status = 127;
		exit(EXIT_FAILURE);
	}
    exit(EXIT_FAILURE);
}

void	run(t_shell *shell, t_exec *exec)
{
    int i;
    int j;
    int *fd;
    t_exec *tmp;

	i = 0;
	j = 0;
	if (exec->cmd == NULL)
		return ;
	fd = (int *)malloc(count_cmmds(exec) * sizeof(int) * 2);
	tmp = exec;
	if (count_cmmds(exec) > 1)
	{
    while (j < count_cmmds(exec) * 2)
    {
        pipe(&fd[j]);
        j += 2;
    }
	}
    j = 0;
    while (tmp)
    {
        int pid = fork();
        if (pid == 0)
        {
            if (tmp->next)
			{
				exec->fd_out = fd[j + 1];
			}
            if (j)
			{
				exec->fd_in = fd[j - 2];
			}
        	dup2(exec->fd_out, 1);
			dup2(exec->fd_in, 0);
            close_all(fd, count_cmmds(exec) * 2);
			char *path;
			path = find_exec(shell, tmp->cmd);
            execute_command(shell, tmp, path);
            exit(0);
        }
		else
			waitpid(pid, &shell->exit_status, 0);
        i++;
        j += 2;
        tmp = tmp->next;
    }
	// if (exec->fd_in != 0)
	// 	close(exec->fd_in);
	// if (exec->fd_out != 1)
	// 	close(exec->fd_out);
    // close_all(fd, count_cmmds(exec) * 2);
}
