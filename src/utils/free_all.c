/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:43 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/14 17:10:28 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_all(t_shell *shell)
{
    int i;

    i = 0;
    i = 0;
    while (shell->cmd[i])
    {
        free(shell->cmd[i]);
        i++;
    }
    free(shell->cmd);
    free(shell->line);
    while (shell->token)
    {
        free(shell->token->content);
        free(shell->token);
        shell->token = shell->token->next;
    }
}