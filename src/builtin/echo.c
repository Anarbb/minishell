/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:07:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/10 13:02:33 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_exec *exec)
{
	int		i;
	int		j;
	int	new_line;
	
	i = 1;
	new_line = 1;
	while (exec->args[i] && ft_strcmp(exec->args[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	j = i;
	while (exec->args[j])
	{
		ft_putstr_fd(exec->args[j], 1);
		j++;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
