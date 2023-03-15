/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:52:08 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/15 15:16:29 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// void	init_pipesfd(t_exec *exec, int **fd, int j)
// {
//     if (!exec->prev && exec->next)
// 	{
// 		if (exec->fd_out == 1)
// 			exec->fd_out = fd[j][1];
// 	}
// 	else if (exec->prev && exec->next)
// 	{
// 		if (exec->fd_out == 1)
// 			exec->fd_out = fd[j][1];
// 		if (exec->fd_in == 0)
// 			exec->fd_in = fd[j - 1][0];
// 	}
// 	else if (exec->prev && !exec->next)
// 	{
// 		if (exec->fd_in == 0)
// 			exec->fd_in = fd[j - 1][0];
// 	}
// }
                                                   
// void	pipe_handler(t_exec *exec)
// {
// 	int	**fd;
// 	int	j;
// 	int	nbr_cmds;;

// 	j = 0;
// 	nbr_cmds = count_commands(exec) - 1;
// 	fd = malloc(sizeof(int *) * nbr_cmds);
// 	if (!fd)
// 		exit(1);
// 	while (j < nbr_cmds)
// 	{
// 		fd[j] = malloc(sizeof(int) * 2);
// 		if (!fd[j])
// 			exit(1);
// 		if (pipe(fd[j]) == -1)
// 			exit(EXIT_FAILURE);
// 		j++;
// 	}
// 	j = 0;
// 	while (exec)
// 	{
// 		init_pipesfd(exec, fd, j);
// 		j++;
// 		exec = exec->next;
// 	}
// }
// 	fd = (int *)malloc(count_cmmds(exec) * sizeof(int) * 2);
// 	tmp = exec;
// 	if (count_cmmds(exec) > 1)
// 	{
//     while (j < count_cmmds(exec) * 2)
//     {
//         pipe(&fd[j]);
//         j += 2;
//     }
	// }