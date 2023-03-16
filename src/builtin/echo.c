/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:07:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/16 20:56:22 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_exec *exec)
{
	int		i;
	int		new_line;
	char	**args;

	i = 1;
	new_line = 1;
	args = exec->args;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		int j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			new_line = 0;
		}
		else
			break;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
