/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:52:08 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/15 21:15:18 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

void	pipesfd(t_exec *exec, int **fd, int j)
{
    if (j == 0 && exec->next)
	{
		if (exec->fd_out == 1)
			exec->fd_out = fd[j][1];
	}
	else if (j != 0 && exec->next)
	{
		if (exec->fd_out == 1)
			exec->fd_out = fd[j][1];
		if (exec->fd_in == 0)
			exec->fd_in = fd[j - 1][0];
	}
	else if (!exec->next)
	{
		if (exec->fd_in == 0)
			exec->fd_in = fd[j - 1][0];
		exec->fd_out = 1;
	}
}

int	**pipe_handler(t_exec *exec)
{
	int	**fd;
	int	j;
	int	nbr_cmds;;

	j = 0;
	nbr_cmds = count_commands(exec) - 1;
	fd = malloc(sizeof(int *) * nbr_cmds);
	if (!fd)
		exit(1);
	while (j < nbr_cmds)
	{
		fd[j] = malloc(sizeof(int) * 2);
		if (!fd[j])
			exit(1);
		if (pipe(fd[j]) == -1)
			exit(EXIT_FAILURE);
		j++;
	}
	j = 0;
	while (exec)
	{
		pipesfd(exec, fd, j);
		j++;
		exec = exec->next;
	}
	return (fd);
}
