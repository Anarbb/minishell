/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:43 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/17 14:45:15 by aarbaoui         ###   ########.fr       */
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


void    free_all(t_shell *shell)
{
    int i;

    i = -1;
    if (shell->cmd)
    {
        while (shell->cmd[++i])
            free(shell->cmd[i]);
        free(shell->cmd);
    }
	free(shell->cwd);
	free(shell->line);
    free_tokens(&shell->token);
}