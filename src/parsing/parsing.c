/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/11 21:04:32 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*limiter_path(char *limiter)
{
	char		*new_limtr;
	static int	i;

	new_limtr = (char *)malloc(sizeof(char) * (ft_strlen(limiter) + 8));
	if (!new_limtr)
		return (NULL);
	ft_strcpy(new_limtr, "/tmp/.");
	ft_strcat(new_limtr, limiter);
	ft_strcat(new_limtr, ft_itoa(i));
	i++;
	return (new_limtr);
}

int	checker(t_exec *tmp)
{
	if (tmp->prev == NULL)
		return (1);
	return ((tmp->type == CMD || tmp->type == DOLLAR)
		&& tmp->prev->type != REDIR_OUT
		&& tmp->prev->type != REDIR_APPEND && tmp->prev->type != REDIR_IN
		&& tmp->prev->type != HERDOC && tmp->type != SPACE_MS );
}
void	parsing(t_shell *shell)
{
	t_exec	*tmp;
	char	**args;
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 1;
	tmp = shell->exec;
	args = (char **)ft_calloc(exec_size(tmp) + 1, sizeof(char *));
	// shell->exec->args = args;
	while (tmp)
	{
		// if ((tmp && tmp->cmd) && checker(tmp))
		// {
		// 		*args = ft_strdup(tmp->cmd);
		// 		args++;
		// 		if (tmp)
		// 			*args = NULL;
	
		// }
		if (tmp->type == REDIR_OUT)
			fd_out = open(tmp->next->cmd,
					O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC, 0664);
		if (tmp->type == REDIR_APPEND)
			fd_out = open(tmp->next->cmd,
					O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND, 0664);
		else if (tmp->type == REDIR_IN)
		{
			fd_in = open(tmp->next->cmd, O_RDONLY | O_CLOEXEC);
			if (fd_in == -1)
				printf("minishell: %s: No such file or directory\n",
						tmp->next->cmd);
		}
		else if (tmp->type == HERDOC)
		{
			int fd;
			signal(SIGINT, NULL);
			fd = open(limiter_path(tmp->next->cmd), O_CREAT | O_RDWR, 0777);
			if (fd == -1)
				printf("minishell: error: heredoc\n");
			tmp->herdoc = 1;
			shell->exec->limiter = ft_strdup(tmp->next->cmd);
			handle_heredoc(shell->exec, fd);
		}
		tmp = tmp->next;
	}
	shell->exec->fd_in = fd_in;
	shell->exec->fd_out = fd_out;
	// exec_clear(&shell->exec->next);
	// t_exec *tmp121 = shell->exec;
	// my_printf("tmp121 : %s", tmp121->next->cmd);
}
