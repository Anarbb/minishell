/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/02 16:30:04 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_shell *shell)
{
	t_exec	*exec;
	t_exec	*tmp;
	char	**args;
	int 	i;
	
	i = 0;
	exec = NULL;
	tmp = shell->exec;
	args = (char **)ft_calloc(exec_size(exec), sizeof(char *));
	while (tmp)
	{
		printf("tmp->bin: %s\n", tmp->bin);
		if (tmp && tmp->type == CMD)
		{
			args[i] = ft_strdup(tmp->bin);
			i++;
		}
		tmp = tmp->next;
	}
	shell->exec->args = args;
	shell->exec->fd_in = 0;
	shell->exec->fd_out = 1;
	exec_clear(&shell->exec->next);
}
