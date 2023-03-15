/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:24:25 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/15 21:29:17 by lsabik           ###   ########.fr       */
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

void	handle_heredoc(t_shell *shell, int fd)
{
	char	*line;

	shell->exec->fd_in = fd;
	while (1)
	{
		signal(SIGINT, sig_handl);
		line = readline("> ");
		if (gvars->herdoc == 0)
		{
			gvars->herdoc = 1;
			free(line);
			signal(SIGINT, sig_handler);
			return ;
		}
		if (line == NULL)
			return ;
		if (gvars->inside_quotes == WITHOUT_QUOTES)
			line = expand_heredoc(shell, line, 0);
		if (ft_strcmp(line, shell->exec->limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
	// lseek(fd, 0 , SEEK_SET);
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


void close_all(int **fd, int nbr, t_exec *exec)
{
    int i;
	t_exec	*tmp;

    i = 0;

	tmp = exec;
	while (tmp)
	{
		if (tmp->fd_in != 0)
			close(tmp->fd_in);
		if (tmp->fd_out != 1)
			close(tmp->fd_out);
		tmp = tmp->next;
	}
    while (i < nbr)
    {
        close(fd[i][1]);
        close(fd[i][0]);
        i++;
    }
	i = 0;
	while (i < nbr)
		free(fd[i++]);
	free(fd);
}

void execute_command(t_shell *shell, t_exec *exec, char *path)
{
	if (execve(path, exec->args, shell->env_arr) == -1)
	{
		printf("minishell: %s: command not found\n", exec->args[0]);
		shell->exit_status = 127;
		exit(EXIT_FAILURE);
	}
}
void execute_single_cmd(t_exec *tmp, t_shell *shell)
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
	waitpid(-1, 0, 0) ;
}
void	execute(t_shell *shell, t_exec *exec, int **pipefd, int j)
{
    pid_t	pid;
	char *path;

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
		tmp->fd_in = open(gvars->limiter_file, O_CREAT | O_RDWR, 0777);
	if (!tmp->next)
	{
		execute_single_cmd(tmp, shell);
		return;
	}
	pipefd = malloc(sizeof(int) * (j -1));
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
	while(wait(NULL) != -1);
	// waitpid(-1, 0, 0);
	// waitpid(-1, 0, 0);
}