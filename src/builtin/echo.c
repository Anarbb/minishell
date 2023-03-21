/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:07:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/21 18:09:41 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_exec *exec, int i, int new_line)
{
	int		j;
	char	**args;

	args = exec->args;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			new_line = 0;
		else
			break ;
		i++;
	}
	while (args[i])
	{
		ft_putstr(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return (0);
}
