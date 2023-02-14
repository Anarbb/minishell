/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:06:15 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/13 17:06:27 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_add_back(t_token **alst, t_token *new)
{
    t_token *tmp;

    if (alst && new)
    {
        if (*alst == NULL)
            *alst = new;
        else
        {
            tmp = *alst;
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = new;
        }
    }
}