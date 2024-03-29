/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:52:08 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/20 18:17:24 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmmds(t_exec *exec)
{
	t_exec	*tmp;
	int		count;

	count = 0;
	tmp = exec;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	pipesfd(t_exec *exec, int **fd)
{
	int	i;

	i = 0;
	while (exec)
	{
		if (i == 0 && exec->next)
		{
			if (exec->fd_out == 1)
				exec->fd_out = fd[i][1];
		}
		else if (i != 0 && exec->next)
		{
			if (exec->fd_out == 1)
				exec->fd_out = fd[i][1];
			if (exec->fd_in == 0)
				exec->fd_in = fd[i - 1][0];
		}
		else if (i != 0 && !exec->next)
		{
			if (exec->fd_in == 0)
				exec->fd_in = fd[i - 1][0];
		}
		i++;
		exec = exec->next;
	}
}

int	**pipe_handler(t_exec *exec)
{
	int	**fd;
	int	j;
	int	nbr_cmds;

	j = 0;
	nbr_cmds = count_commands(exec) - 1;
	fd = malloc(sizeof(int *) * nbr_cmds);
	if (!fd)
		exit(1);
	while (j < nbr_cmds)
	{
		fd[j] = malloc(sizeof(int) * 2);
		if (!fd[j])
			exit(EXIT_FAILURE);
		if (pipe(fd[j]) == -1)
			exit(EXIT_FAILURE);
		j++;
	}
	pipesfd(exec, fd);
	return (fd);
}

void	close_all(int **fd, int nbr, t_exec *exec)
{
	int		i;
	t_exec	*tmp;

	tmp = exec;
	while (tmp)
	{
		if (tmp->fd_in != 0)
			close(tmp->fd_in);
		if (tmp->fd_out != 1)
			close(tmp->fd_out);
		tmp = tmp->next;
	}
	i = 0;
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

void	execute_command(t_shell *shell, t_exec *exec, char *path)
{
	if (execve(path, exec->args, shell->env_arr) == -1)
	{
		if (errno == EACCES)
			printf("minishell: %s: Permission denied\n", exec->args[0]);
		if (errno == ENOENT)
			printf("minishell: %s: No such file or directory\n", exec->args[0]);
		else
			printf("minishell: %s: command not found\n", exec->args[0]);
		exit(127);
	}
}
