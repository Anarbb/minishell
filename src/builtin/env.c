/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:35:12 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/17 17:01:57 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		ft_putstr_fd(env->var, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
}
