/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:13:41 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/21 18:37:43 by aarbaoui         ###   ########.fr       */
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
		if (check_key_exists(exec->args[i], shell))
			unset_env(shell, exec->args[i]);
		else
			printf("minishell: unset: `%s': not a valid identifier\n", \
				exec->args[i]);
		i++;
	}
	shell->exit_status = 0;
}
