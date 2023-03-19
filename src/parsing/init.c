/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:42:55 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 14:07:50 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path(t_shell *shell, int flaunch)
{
	char	*path;
	char	**paths;
	int		i;

	path = get_env(shell, "PATH");
	if (path == NULL)
	{
		if (!flaunch)
		{
			path = ft_strdup("");
			shell->path = ft_split(path, ':');
			return (0);
		}
		path = ft_strdup("/bin");
		add_env(shell, "PATH", path);
	}
	paths = ft_split(path, ':');
	i = 0;
	char *tmp;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	shell->path = paths;
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

	g_sigflag = 1;
	shell->env_arr = env;
	shell->inside_quotes = WITHOUT_QUOTES;
	init_env(shell);
	// find_path(shell, 1);
	shlvl = get_shlvl(shell);
	set_env(shell, "SHLVL", shlvl);
	free(shlvl);
}
