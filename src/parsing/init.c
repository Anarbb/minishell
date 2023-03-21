/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:42:55 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/21 15:01:34 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path(t_shell *shell, int flaunch, int i)
{
	char	*path;
	char	**paths;

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
	while (paths[i])
	{
		paths[i] = ft_join(paths[i], "/");
		i++;
	}
	return (shell->path = paths, 1);
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
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	g_sigflag = 1;
	shell->env_arr = env;
	shell->pid_idx = 0;
	shell->inside_quotes = WITHOUT_QUOTES;
	init_env(shell);
	shlvl = get_shlvl(shell);
	set_env(shell, "SHLVL", shlvl);
	if (!env[0])
	{
		add_env(shell, "PATH", "/bin");
		add_env(shell, "SHLVL", "1");
		add_env(shell, "PWD", pwd);
	}
	free(pwd);
	free(shlvl);
}
