/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:07:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/04 10:11:45 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_shell *shell)
{
	int		i;
	int		j;
	int	new_line;

	i = 1;
	new_line = 1;
	while(shell->cmd[i] && shell->cmd[i][0] == '-' && shell->cmd[i][1] == 'n')
	{
		j = 1;
		while(shell->cmd[i][j] == 'n')
			j++;
		if (shell->cmd[i][j] == '\0')
			new_line = 0;
		else
			break;
		i++;
	}
	while (shell->cmd[i])
	{
		ft_putstr_fd(shell->cmd[i++], 1);
		if (shell->cmd[i])
			write(1, " ", 1);
	}
	if (new_line == 1)
		write(1, "\n", 1);
	return (SUCCESS);
}
