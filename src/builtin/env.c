/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:35:12 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/21 20:20:28 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	if (arg_count(shell->exec->args) > 1)
	{
		printf("minishell: env: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	while (env)
	{
		if (env->value && env->shown)
		{
			ft_putstr(env->var, 1);
			ft_putstr("=", 1);
			ft_putendl_fd(env->value, 1);
		}
		env = env->next;
	}
	shell->exit_status = 0;
}
