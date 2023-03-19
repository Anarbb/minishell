/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:43 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 18:51:14 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*aux_lst;

	if (*tokens)
	{
		while (*tokens)
		{
			aux_lst = (*tokens)->next;
			free((*tokens)->content);
			free(*tokens);
			*tokens = aux_lst;
		}
		*tokens = NULL;
	}
}

void	exec_clear(t_exec **exec)
{
	t_exec	*ptr;
	t_exec	*next;

	if (!exec)
		return ;
	ptr = *exec;
	while (ptr)
	{
		next = ptr->next;
		free(ptr->cmd);
		free(ptr);
		ptr = next;
	}
	*exec = NULL;
}

void	free_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		free(shell->cmd[i]);
		i++;
	}
	free(shell->cmd);
}

void	free_all(t_shell *shell)
{
	free(shell->line);
	exec_clear(&shell->exec);
	free_tokens(&shell->token);
}
