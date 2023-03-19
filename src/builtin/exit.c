/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:01:34 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/19 18:27:54 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, int flag)
{
	t_exec	*exec;
	int		i;

	i = 0;
	exec = shell->exec;
	if (arg_count(exec->args) > 2)
		return (printf("exit\nminishell: exit: too many arguments\n"), 1);
	if (exec->args[1])
	{
		if (exec->args[1][0] == '-' && !exec->args[1][1])
			exit(255);
		while (ft_isdigit(exec->args[1][i]) || exec->args[1][i] == '-')
		{
			if (!ft_isdigit(exec->args[1][i]) && exec->args[1][i] != '-')
				flag++;
			i++;
		}
		if (exec->args[1][i] || flag > 1)
			exit(255);
		else
			exit(ft_atoi(exec->args[1]));
	}
	else
		exit(0);
	return (0);
}
