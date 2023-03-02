/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:43 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/02 13:49:50 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*ptr;
	t_token	*next;

	if (!tokens)
		return ;
	ptr = *tokens;
	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
	*tokens = NULL;
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
		free(ptr->bin);
		free(ptr);
		ptr = next;
	}
	*exec = NULL;
}

void	free_all(t_shell *shell)
{
	free(shell->cwd);
	free(shell->line);
	exec_clear(&shell->exec);
	free_tokens(&shell->token);
}