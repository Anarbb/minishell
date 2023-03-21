/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:27 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/21 16:38:49 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd2(t_shell *shell, char *home, char *pwd)
{
	char	*oldpwd;

	oldpwd = get_env(shell, "PWD");
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("cd: error retrieving current directory: getcwd: cannot \
			access parent directories: No such file or directory\n");
		chdir(home);
		pwd = getcwd(NULL, 0);
		set_env(shell, "OLDPWD", oldpwd);
		set_env(shell, "PWD", pwd);
		return (shell->exit_status = 1);
	}
	if (check_key_exists("OLDPWD", shell))
		set_env(shell, "OLDPWD", oldpwd);
	else
		add_env(shell, "OLDPWD", oldpwd);
	set_env(shell, "PWD", pwd);
	free(pwd);
	return (shell->exit_status = 0);
}

int	ft_cd(t_shell *shell, t_exec *exec, char *home, char *pwd)
{
	home = get_env(shell, "HOME");
	if (!exec->args[1] || ft_strcmp(exec->args[1], "~") == 0)
	{
		if (home)
		{
			if (chdir(home) == -1)
			{
				perror("minishell: cd");
				return (shell->exit_status = 1);
			}
			else
				return (ft_cd2(shell, home, pwd));
		}
		else
			return (ft_putstr("minishell: cd: HOME not set\n", 2), \
				shell->exit_status = 1);
	}
	else if (ft_strcmp(exec->args[1], "-") == 0)
	{
		printf("%s\n", get_env(shell, "OLDPWD"));
		chdir(get_env(shell, "OLDPWD"));
	}
	else if (chdir(exec->args[1]) == -1)
		return (perror("minishell: cd"), shell->exit_status = 1);
	else
		return (ft_cd2(shell, home, pwd));
	return (shell->exit_status = 0);
}
