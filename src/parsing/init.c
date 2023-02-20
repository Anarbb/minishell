/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:42:55 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/20 16:32:59 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_path(t_shell *shell)
{
	char *path;

    path = get_env(shell, "PATH");
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
    shell->tmp_env = env;
    init_env(shell);
    if (get_env(shell, "SHLVL") == NULL)
        set_env(shell, "SHLVL", "1");
    else
        set_env(shell, "SHLVL", ft_itoa(ft_atoi(get_env(shell, "SHLVL")) + 1));
    if (!find_path(shell))
        exit(0);
}