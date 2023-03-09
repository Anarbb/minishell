/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:52:08 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/09 21:45:30 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	pipes(int *fd)
{
	char buf[15];
	pid_t	pid;

	pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) { // child process
        close(fd[0]); // close the read end of the pipe
        write(fd[1], "Hello, parent!", 15); // write to the pipe
        close(fd[1]); // close the write end of the pipe
        exit(0); // exit the child process
    } else { // parent process
        close(fd[1]); // close the write end of the pipe
        read(fd[0], buf, 15); // read from the pipe
        printf("Parent received: %s\n", buf);
        close(fd[0]); // close the read end of the pipe
    }
}

void	exection(t_exec *exec)
{
	int	fd[2];

	while (exec->cmd)
	{
		if (exec->type == PIPE)
		{
			if (pipe(fd) == -1)
				exit(EXIT_FAILURE);
			pipes(fd);
		}
		exec = exec->next;
	}
}