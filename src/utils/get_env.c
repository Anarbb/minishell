/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:57 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/10 18:39:02 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env(char **env, char *name)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(name);
    while (env[i])
    {
        if (ft_strncmp(env[i], name, len) == 0)
            return (ft_strndup(env[i] + len + 1, ft_strlen(env[i]) - len));
        i++;
    }
    return (NULL);
}