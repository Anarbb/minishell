/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:53:34 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/18 20:24:32 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_exec *exec)
{
	int	count;

	count = 0;
	while (exec)
	{
		count++;
		exec = exec->next;
	}
	return (count);
}

int	execute_Fbuiltins(t_exec *exec, t_shell *shell)
{
	if (ft_strcmp(exec->cmd, "cd") == 0)
		ft_cd(shell, exec);
	else if (ft_strcmp(exec->cmd, "echo") == 0)
		ft_echo(exec);
	else if (ft_strcmp(exec->cmd, "export") == 0)
		ft_export(shell, exec);
	else if (ft_strcmp(exec->cmd, "unset") == 0)
		ft_unset(shell);
	else if (ft_strcmp(exec->cmd, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(exec->cmd, "exit") == 0)
		ft_exit(shell);
	else
		return (FAILURE);
	return (SUCCESS);
}
