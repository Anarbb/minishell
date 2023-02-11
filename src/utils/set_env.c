/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:37:48 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/11 15:02:02 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_env(t_shell *shell, char *name, char *value)
{
    int i;
    int len;
    char *tmp;

    i = 0;
    len = ft_strlen(name);
    while (shell->env[i])
    {
        if (ft_strncmp(shell->env[i], name, len) == 0)
        {
            tmp = ft_strjoin(name, "=");
            shell->env[i] = ft_strjoin(tmp, value);
            free(tmp);
            return ;
        }
        i++;
    }
    shell->env[i] = ft_strjoin(name, "=");
    shell->env[i] = ft_strjoin(shell->env[i], value);
    
}