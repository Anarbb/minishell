/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/15 15:02:18 by lsabik           ###   ########.fr       */
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
	pid_t	pid;

	pid = fork();
	while (1 && pid == 0)
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
	waitpid(pid, NULL, 0);
	exec->fd_in = fd;
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


void close_all(int *fd)
{
    int i;

    i = 0;
    while (i < 2)
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
void	init_pipesfd(t_exec *exec, int **fd, int j)
{
    if (!exec->prev && exec->next)
	{
		if (exec->fd_out == 1)
			exec->fd_out = fd[j][1];
	}
	else if (exec->prev && exec->next)
	{
		if (exec->fd_out == 1)
			exec->fd_out = fd[j][1];
		if (exec->fd_in == 0)
			exec->fd_in = fd[j - 1][0];
	}
	else if (exec->prev && !exec->next)
	{
		if (exec->fd_in == 0)
			exec->fd_in = fd[j - 1][0];
	}
}

int	*pipe_handler(t_shell *shell, t_exec *exec)
{
	int	pid;
	int	pipefd[2];
	int	n;
	char *path;
	
	path = find_exec(shell, exec->cmd);
	n = pipe(pipefd);
	if (n == -1)
		errors(2);
	
	pid = fork();
	if (pid == -1)
		errors(3);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_command(shell, exec, path);
		// close_all(pipe);
	}
	else
	{
		wait(NULL);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
	}
	
}
void	run(t_shell *shell, t_exec *exec)
{
    int		i;
    int		j;
    int		*pipe;
    t_exec	*tmp;

	i = 0;
	j = 0;
	tmp = exec;
	if (exec->cmd == NULL)
		return ;
    while (tmp)
    {
		pipe = pipe_handler(shell, tmp);
        tmp = tmp->next;
    }
    close_all(pipe);
}
        // int pid = fork();
        // if (pid == 0)
        // {
			// if (exec->fd_out != 1)
        	// 	dup2(exec->fd_out, 1);
			// if (exec->fd_in != 0)
			// 	dup2(exec->fd_in, 0);
            // close_all(pipe);
			// char *path;
			// path = find_exec(shell, tmp->cmd);
            // execute_command(shell, tmp, path);
            // exit(0);
        // }
		// else
			// waitpid(pid, &shell->exit_status, 0);
        // i++;
        // j += 2;