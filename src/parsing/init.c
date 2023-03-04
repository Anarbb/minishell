/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:42:55 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/04 15:34:00 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_path(t_shell *shell)
{
	char *path;

	path = get_env(shell, "PATH");
	if (path == NULL)
	{
		shell->env = ft_calloc(1, sizeof(t_env));
		shell->env->var = ft_strdup("PATH");
		shell->env->value = ft_strdup("/bin");
		shell->env->next = NULL;
		path = ft_strdup("/bin");
	}
	shell->path = ft_split(path, ':');
	free(path);
	return (1);
}



void    init_shell(t_shell *shell, char **env)
{
	char    *shlvlc;
	int     shlvl;

	shlvl = 1;
	shell->env_arr = env;
	shlvlc = ft_itoa(shlvl);
	init_env(shell);
	if (!find_path(shell))
		exit(0);
	if (get_env(shell, "SHLVL") == NULL)
		set_env(shell, "SHLVL", shlvlc);
	else
	{
		shlvlc = ft_itoa(ft_atoi(get_env(shell, "SHLVL")) + 1);
		set_env(shell, "SHLVL", shlvlc);
	}
	free(shlvlc);
}