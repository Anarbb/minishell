/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:33:10 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/15 17:04:12 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *token_new(char *cmd, int type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->content = cmd;
    new->type = type;
    new->next = NULL;
    return (new);
}

void    token_add_b(t_token *tokens, t_token *new)
{
    t_token *ptr;
    
    if (!tokens)
    {
        tokens = new;
        return ;
    }
    ptr = tokens;
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = new;
}