/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:53:34 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/13 12:54:35 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int count_commands(t_exec *exec)
{
    int count;

    count = 0;
    while (exec)
    {
        count++;
        exec = exec->next;
    }
    return (count);
}
