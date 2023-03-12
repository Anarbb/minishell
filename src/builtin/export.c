/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/12 18:10:30 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_export(t_shell *shell, t_exec *exec)
{
	int		i;
	int		j;
	char	*var;
	char	*value;

	i = 1;
	if (!exec->args[1])
		print_env(shell);
	while (exec->args[i])
	{
		j = 0;
		while (exec->args[i][j] && exec->args[i][j] != '=')
			j++;
		var = ft_substr(exec->args[i], 0, j);
		if (exec->args[i][j] == '=')
			value = ft_substr(exec->args[i], j + 1, ft_strlen(exec->args[i]));
		else
			value = ft_strdup("");
		set_env(shell, var, value);
		free(var);
		free(value);
		i++;
	}
}
