/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/12 17:10:11 by lsabik           ###   ########.fr       */
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
// bash 3
// miniexec 4
// minhsell 4

void	exec_cmd(t_shell *shell, t_exec *exec, char *path)
{
	pid_t	pid;
	
	int		status;
	// char **args;
	

	
	// if (path == NULL)
	// {
	// 	args = exec->args;
	// 	*args = exec->cmd;
	// 	args++;
	// 	*args = NULL;
	// 	path = exec->cmd;
	// }
	pid = fork();
	if (pid == 0)
	{
		dup2(exec->fd_in, 0);
		dup2(exec->fd_out, 1);
		// printf("|path %s|\n", exec->args);	
		if (ft_strcmp(exec->cmd, "echo") == 0)
			ft_echo(exec);
		if (execve(path, exec->args, shell->env_arr) == -1)
		{
			printf("minishell: %s: command not found\n", exec->args[0]);
			shell->exit_status = 127;
			exit(EXIT_FAILURE);
		}
		close(exec->fd_in);
		close(exec->fd_out);
	} 
	if (exec->fd_in != 0)
		close(exec->fd_in);
	if (exec->fd_out != 1)
		close(exec->fd_out);
	waitpid(pid, &status, 0);
}
void	handle_heredoc(t_exec *exec, int fd)
{
	char	*line;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			gvars->herdoc = 0;
			line = readline("> ");
			signal(SIGINT, sig_handler);
			if (line == NULL)
				return ;
			if (ft_strcmp(line, exec->limiter) == 0)
			{
				free(line);
				return ;
			}
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
		}
	}
	waitpid(pid, &status,0);
}

void	run(t_shell *shell, t_exec *exec)
{
	(void)shell;
	while (exec)
	{

		// if cmd first and next type is pipe	: in=0		out=pipe
		// if cmd first and next type is pipe	: in=pipe	out=pipe
		// if cmd LAST and next type null		: in=pipe	out=1
		pipe_handler(exec);
		if (ft_strcmp(exec->cmd, "cd") == 0)
			ft_cd(shell, exec);
		else if (ft_strcmp(exec->cmd, "export") == 0)
			ft_export(shell, exec);
		else if (ft_strcmp(exec->cmd, "unset") == 0)
			ft_unset(shell);
		else if (ft_strcmp(exec->cmd, "env") == 0)
			ft_env(shell);
		else if (ft_strcmp(exec->cmd, "exit") == 0)
			ft_exit(shell);
		else
    	{
			// printf("------> %s\n", exec->args[1]);
			if (exec->type == CMD)
    	    {
				exec->cmd = find_exec(shell, exec->cmd);
    	    	exec_cmd(shell, exec, exec->cmd);
			}
    	}
		exec= exec->next;
	}
}