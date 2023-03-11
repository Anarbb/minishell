/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:52:08 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/11 18:21:26 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	pipes(t_exec *exec, int *fd)
{
    
	if (exec->fd_out == 1)
		exec->fd_out = fd[1];
	if (exec->next->next->fd_in == 0)
	exec->next->next->fd_in = fd[0];
}
                                                   
void	pipe_handler(t_exec *exec)
{
    // int **fd;
	int	fd[2];

	if (exec->next && exec->next->type == PIPE)
	{
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pipes(exec, fd);
	}
}