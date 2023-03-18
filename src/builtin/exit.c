/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:01:34 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/18 14:50:46 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell)
{
	t_exec	*exec;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	exec = shell->exec;
	if (arg_count(exec->args) > 2)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
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
