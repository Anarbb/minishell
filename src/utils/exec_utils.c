/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:30:01 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/11 22:48:22 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*exec_new(char *tmp, int type)
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	exec->cmd = ft_strdup(tmp);
	exec->limiter = NULL;
	exec->type = type;
	exec->fd_in = 0;
	exec->fd_out = 1;
	exec->herdoc = 0;
	exec->next = NULL;
	exec->prev = NULL;
	return (exec);
}

void	exec_add_b(t_shell *shell, char *tmp, int type)
{
	t_exec	*new;
	t_exec	*tmp_exec;

	new = exec_new(tmp, type);
	tmp_exec = shell->exec;
	while (tmp_exec->next)
		tmp_exec = tmp_exec->next;
	tmp_exec->next = new;
	new->prev = tmp_exec;
}

int	exec_size(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec)
	{
		i++;
		exec = exec->next;
	}
	return (i);
}

void	exec_create(t_shell *shell, char *tmp, int type)
{
	if (shell->exec == NULL)
		shell->exec = exec_new(tmp, type);
	else
		exec_add_b(shell, tmp, type);
}
