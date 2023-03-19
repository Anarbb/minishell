/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:35:12 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 18:20:21 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		ft_putstr(env->var, 1);
		ft_putstr("=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
}
