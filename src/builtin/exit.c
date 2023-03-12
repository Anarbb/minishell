/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:01:34 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/12 18:10:34 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell)
{
	t_exec	*exec;

	exec = shell->exec;
	if (exec->args[1])
	{
		if (ft_isdigit(exec->args[1][0]))
			exit(ft_atoi(exec->args[1]));
		else
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(exec->args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (1);
		}
	}
	else
		exit(0);
	return (0);
}
