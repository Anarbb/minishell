/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:42:39 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/26 18:45:16 by lsabik           ###   ########.fr       */
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
	my_printf("%s", shell->cmd[0]);
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
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, &shell->cmd[0], shell->tmp_env) == -1)
			{
				ft_putstr_fd("minishell: command not found: \n", 2);
				ft_putendl_fd(shell->cmd[0], 2);
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	set_env(shell, "_", shell->cmd[0]);
}
// int	dup_and_close(t_data *data, t_cmd *cmd)
// {
// 	dup2(cmd->fd_in, 0);
// 	dup2(cmd->fd_out, 1);
// 	if (cmd->fd_in != 0)
// 		close(cmd->fd_in);
// 	if (cmd->fd_out != 1)
// 		close(cmd->fd_out);
// 	close_fds(cmd);
// 	close_pipes(data->pipes, data->general.count);
// 	g_vars.g_exit_stat = check_builtins(data, cmd);
// 	if (g_vars.g_exit_stat == NO_BUILT)
// 		g_vars.g_exit_stat = execution_2(data, cmd);
// 	return (g_vars.g_exit_stat);
// }

// int	execution(t_data *data, t_cmd *cmd)
// {
// 	int		pid;
// 	int		fork_c;

// 	fork_c = 0;
// 	pid = 1;
// 	while (cmd)
// 	{
// 		g_vars.g_exit_stat = check_nonfork(data, cmd);
// 		if (g_vars.g_heredoc == 0)
// 			return (HEREDOC_EXE);
// 		fork_c += check_fork(&pid, data);
// 		signal(SIGINT, SIG_IGN);
// 		if (pid == 0 && cmd->fd_in != -69)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 			g_vars.g_where_ami = 0;
// 			g_vars.g_exit_stat = dup_and_close(data, cmd);
// 			exit(g_vars.g_exit_stat);
// 		}
// 		cmd = cmd->next;
// 	}
// 	close_all(cmd, data->pipes, data->general.count);
// 	if (fork_c)
// 		g_vars.g_exit_stat = terminate_pid(pid);
// 	return (g_vars.g_exit_stat);
// }

// int	pre_execution(t_data *data)
// {
// 	t_cmd	*cmd;
// 	int		pid;

// 	pid = 0;
// 	data->general.count = c_lstcmd(data);
// 	if (data->lst_cmd)
// 	{
// 		cmd = data->lst_cmd;
// 		data->pipes = initialize_pipes(data);
// 		if (execution(data, cmd) == HEREDOC_EXE)
// 			g_vars.g_exit_stat = 1;
// 	}
// 	return (0);
// }
