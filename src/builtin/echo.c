/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:07:55 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/04 13:44:40 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_shell *shell)
{
	int		i;
	int		j;
	int	new_line;
	t_exec	*exec;

	exec = shell->exec;
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
