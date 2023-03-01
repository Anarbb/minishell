/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/01 13:31:35 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lab(t_shell *shell)
{
	t_exec 	*exec;
	char 	**cmd;
	
	exec = shell->exec;
	cmd = (char **)malloc(sizeof(char *) * (exec_size(shell->exec) + 1));
	while (exec)
	{
		if ((exec->prev && exec->type == CMD)
			&& (exec->prev->type == CMD || exec->prev->type == ARG))
			exec->type = ARG;
		if (exec->type == CMD)
		{
			*cmd = ft_strdup(exec->bin);
			cmd++;
		}
		exec = exec->next;
	}
	return (cmd);
}
