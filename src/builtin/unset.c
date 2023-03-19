/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:41 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 18:10:12 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_shell *shell)
{
	t_exec	*exec;
	int		i;

	exec = shell->exec;
	i = 1;
	while (exec->args[i])
	{
		if (get_env(shell, exec->args[i]))
			unset_env(shell, exec->args[i]);
		else
			printf("minishell: unset: `%s': not a valid identifier\n", \
				exec->args[i]);
		i++;
	}
}
