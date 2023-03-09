/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:41 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/09 16:29:33 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_unset(t_shell *shell)
{
    (void)shell;
    // t_env *tmp;
    // t_env *prev;

    // tmp = shell->env;
    // prev = NULL;
    // while (tmp)
    // {
    //     if (ft_strcmp(tmp->var, var) == 0)
    //     {
    //         if (prev)
    //             prev->next = tmp->next;
    //         else
    //             shell->env = tmp->next;
    //         free(tmp->var);
    //         free(tmp->value);
    //         free(tmp);
    //         return ;
    //     }
    //     prev = tmp;
    //     tmp = tmp->next;
    // }
}

