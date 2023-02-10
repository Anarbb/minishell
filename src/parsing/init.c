/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:42:55 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/10 14:48:28 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_path(t_shell *shell, char **env)
{
	char	*binPath;
    int     i;

    if (!env)
        return (0);
    if (shell->path)
    {
        i = 0;
        while (shell->path[i])
        {
            free(shell->path[i]);
            i++;
        }
        free(shell->path);
    }
	while (ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	binPath = (*env + 5);
	shell->path = ft_split(binPath, ':');
    if (!shell->path)
        return (0);
    return (1);
}

void    init_shell(t_shell *shell, char **env)
{
    shell->cmd = NULL;
    shell->type = 0;
    if (!find_path(shell, env))
        exit(0);
}