/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:07:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/11 20:23:54 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_cmd(t_shell *shell)
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
