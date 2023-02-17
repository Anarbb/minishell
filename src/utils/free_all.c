/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:43 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/17 13:18:38 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tokens(t_token *token)
{
    t_token *tmp;

    while (token)
    {
        tmp = token;
        token = token->next;
        if (tmp->content)
           tmp->content = "";
        tmp->type = 0;
    }
}


void    free_all(t_shell *shell, int tokens)
{
    int i;

    i = -1;
    if (shell->cmd)
    {
        while (shell->cmd[++i])
            free(shell->cmd[i]);
        free(shell->cmd);
    }
    if (tokens)
    {
        free_tokens(shell->token);
    }
}