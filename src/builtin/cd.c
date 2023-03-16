/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:32:27 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/16 20:30:14 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *shell, t_exec *exec)
{
	char	*oldpwd;
	char	*pwd;

	if (!exec->args[1] || ft_strcmp(exec->args[1], "~") == 0)
		chdir(get_env(shell, "HOME"));
	else if (ft_strcmp(exec->args[1], "-") == 0)
	{
		printf("%s\n", get_env(shell, "OLDPWD"));
		chdir(get_env(shell, "OLDPWD"));
	}
	else if (chdir(exec->args[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(exec->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	else
	{
		oldpwd = get_env(shell, "PWD");
		pwd = getcwd(NULL, 0);
		set_env(shell, "OLDPWD", oldpwd);
		set_env(shell, "PWD", pwd);
	}
}
