/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:42:55 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/11 15:11:13 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_path(t_shell *shell, char **env)
{
	char *path;

    path = get_env(env, "PATH");
    if (path == NULL)
    {
        ft_putstr_fd("minishell: PATH not found", 2);
        return (0);
    }
    shell->path = ft_split(path, ':');
    free(path);
    return (1);
}

void    init_shell(t_shell *shell, char **env)
{
    shell->env = env;
    if (!find_path(shell, env))
        exit(0);
}