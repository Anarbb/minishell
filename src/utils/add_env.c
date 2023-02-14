/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:26:01 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/14 15:17:37 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_env(t_shell *shell, char *name, char *value)
{
	int i;
	char *tmp;

	i = 0;
	(void)value;
	while (shell->env[i])
	{
		if (ft_strcmp(shell->env[i], name) == 0)
		{
				tmp = ft_strjoin(shell->env[i], value);
				free(tmp);
				return ;
		}
		i++;
	}
}
