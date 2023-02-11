/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:13:14 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/11 18:29:38 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_cmd(char **cmd)
{
	int		i;
	int		j;
	int	new_line;

	i = 1;
	new_line = 1;
	while(cmd[i] &&cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 1;
		while(cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] == '\0')
			new_line = 0;
		else
			break;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			write(1, " ", 1);
	}
	if (new_line == 1)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
