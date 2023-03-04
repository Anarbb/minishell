/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/04 10:13:07 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_shell *shell)
{
	(void)shell;
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
