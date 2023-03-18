/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:27 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/18 16:53:02 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell *shell, t_exec *exec)
{
	char	*oldpwd;
	char	*pwd;
	char	*home;

	home = get_env(shell, "HOME");
	if (!exec->args[1] || ft_strcmp(exec->args[1], "~") == 0)
	{
		if (home)
		{
			if (chdir(home) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n",
						home);
				return (shell->exit_status = 1);
			}
		}
		else
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (shell->exit_status = 1);
		}
	}
	else if (ft_strcmp(exec->args[1], "-") == 0)
	{
		printf("%s\n", get_env(shell, "OLDPWD"));
		chdir(get_env(shell, "OLDPWD"));
	}
	else if (chdir(exec->args[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", exec->args[1]);
		return (shell->exit_status = 1);
	}
	else
	{
		oldpwd = get_env(shell, "PWD");
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			chdir(home);
			pwd = getcwd(NULL, 0);
			set_env(shell, "OLDPWD", oldpwd);
			set_env(shell, "PWD", pwd);
			return (shell->exit_status = 1);
		}
		set_env(shell, "OLDPWD", oldpwd);
		set_env(shell, "PWD", pwd);
	}
	return (shell->exit_status = 0);
}
