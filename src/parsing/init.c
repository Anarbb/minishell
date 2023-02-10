/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:42:55 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/10 13:46:20 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    find_path(t_shell *shell, char **env)
{
	char	*binPath;

	while (ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	binPath = (*env + 5);
	shell->path = ft_split(binPath, ':');
}

void    init_shell(t_shell *shell, char **env)
{
    shell->cmd = NULL;
    shell->type = 0;
    find_path(shell, env);
}