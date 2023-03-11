/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/10 13:12:42 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_shell *shell, t_exec *exec)
{
	(void)shell;
	(void)exec;
	// t_env *new;
	// t_env *tmp;

	// tmp = shell->env;
	// if (!key || !value)
	// {
	// 	while (tmp)
	// 	{
	// 		printf("declare -x %s=\"%s\"\n",
	// 			   tmp->var, tmp->value);
	// 		tmp = tmp->next;
	// 	}
	// }
	// else
	// {
	// 	new = (t_env *)malloc(sizeof(t_env));
	// 	new->var = ft_strdup(key);
	// 	new->value = ft_strdup(value);
	// 	new->next = NULL;
	// 	if (!shell->env)
	// 		shell->env = new;
	// 	else
	// 		ft_lstadd_back_env(&shell->env, new);
	// }
}
