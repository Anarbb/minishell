/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 11:26:01 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/13 14:05:04 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_env(t_shell *shell, char *name, char *value)
{
	int i;
	int len;
	char *tmp;

	i = 0;
	(void)value;
	len = ft_strlen(name);
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
