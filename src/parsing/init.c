/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:42:55 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/15 17:23:42 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path(t_shell *shell)
{
	char	*path;

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

char	*get_shlvl(t_shell *shell)
{
	char	*shlvl;
	char	*shlvlc;
	int		i;

	i = 0;
	shlvl = get_env(shell, "SHLVL");
	if (shlvl == NULL)
	{
		shlvlc = ft_itoa(1);
		set_env(shell, "SHLVL", shlvlc);
		free(shlvlc);
		return (ft_strdup("1"));
	}
	while (shlvl[i])
	{
		if (!ft_isdigit(shlvl[i]))
			return (ft_strdup("1"));
		i++;
	}
	return (ft_itoa(ft_atoi(shlvl) + 1));
}

void	init_shell(t_shell *shell, char **env)
{
	char	*shlvl;
	gvars = malloc(sizeof(t_global));
	gvars->herdoc = 1;
	gvars->inside_quotes = WITHOUT_QUOTES;
	shell->env_arr = env;
	init_env(shell);
	if (!find_path(shell))
		exit(0);
	shlvl = get_shlvl(shell);
	set_env(shell, "SHLVL", shlvl);
	free(shlvl);
}