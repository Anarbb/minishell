/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/02 20:43:55 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_shell *shell)
{
	t_exec	*exec;
	t_exec	*tmp;
	char	**args;
	int 	i;
	int		fd_in;
	int		fd_out;
	
	i = 0;
	exec = NULL;
	fd_in = 0;
	fd_out = 1;
	tmp = shell->exec;
	args = (char **)ft_calloc(exec_size(exec), sizeof(char *));
	while (tmp)
	{
		// my_printf("tmp->bin: %s", tmp->bin);
		if (tmp && tmp->type == CMD)
		{
			args[i] = ft_strdup(tmp->bin);
			i++;
		}
		if (tmp->type == REDIR_OUT)
			fd_out = open(tmp->next->bin, O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC , 0664);
		if (tmp->type == REDIR_APPEND)
			fd_out = open(tmp->next->bin, O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND , 0664);
		else if (tmp->type == REDIR_IN)
		{
			fd_in = open(tmp->next->bin, O_RDONLY | O_CLOEXEC);
			if (fd_in < 0)
			{
				printf("%s: No such file or directory\n", tmp->next->bin);
				shell->exit_status = 1;
			}
		}
		tmp = tmp->next;
	}
	shell->exec->args = args;
	shell->exec->fd_in = fd_in;
	shell->exec->fd_out = fd_out;
	// my_printf("fd_in:%d",shell->exec->fd_in);
	// my_printf("fd_out:%d",shell->exec->fd_out);
	exec_clear(&shell->exec->next);
}
