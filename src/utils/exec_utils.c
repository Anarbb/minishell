/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:30:01 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/02 13:49:46 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_exec	*exec_new(char *tmp, int type)
{
	t_exec	*exec;

	exec = (t_exec *)ft_calloc(1, sizeof(t_exec));
	exec->bin = ft_strdup(tmp);
	exec->type = type;
	exec->fd_in = 0;
	exec->fd_out = 1;
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

int		exec_size(t_exec *exec)
{
	int		i;

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
