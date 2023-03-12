/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:07:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/12 18:04:53 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// echo with the -n option that bahaves like the echo command in bash
int	ft_echo(t_exec *exec)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (exec->args[1] && ft_strcmp(exec->args[1], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (exec->args[i])
	{
		ft_putstr_fd(exec->args[i], 1);
		if (exec->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);	
}
