/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/04 13:24:24 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_shell *shell)
{
	t_exec	*tmp;
	char	**args;
	int 	i;
	int		fd_in;
	int		fd_out;
	
	i = 0;
	fd_in = 0;
	fd_out = 1;
	tmp = shell->exec;
	args = (char **)ft_calloc(exec_size(tmp) + 1, sizeof(char *));

	while (tmp)
	{
		// my_printf("tmp->bin: %s, tmp->type: %d", tmp->bin, tmp->type);
		if (tmp && tmp->type == CMD && tmp->bin)
		{
			args[i] = ft_strdup(tmp->bin);
			i++;
		}
		if (tmp->type == REDIR_OUT)
		{
			fd_out = open(tmp->next->bin, O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC, 0664);
			break ;
		}
		if (tmp->type == REDIR_APPEND)
		{
			fd_out = open(tmp->next->bin, O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND, 0664);
			break ;
		}
		else if (tmp->type == REDIR_IN)
		{
			fd_in = open(tmp->next->bin, O_RDONLY | O_CLOEXEC);
			if (fd_in == -1)
				printf("minishell: %s: No such file or directory", tmp->next->bin);
			break ;
		}
		tmp = tmp->next;
	}
	args[i] = NULL;
	shell->exec->args = args;
	shell->exec->fd_in = fd_in;
	shell->exec->fd_out = fd_out;
	// my_printf("fd_in:%d",shell->exec->fd_in);
	// my_printf("fd_out:%d",shell->exec->fd_out);
	exec_clear(&shell->exec->next);
}
