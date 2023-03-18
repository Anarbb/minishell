/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/18 15:32:09 by aarbaoui         ###   ########.fr       */
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

// use add_env to add a new env variable and set_env to update an existing one if arg is of the form "$key=value"
void	ft_export(t_shell *shell, t_exec *exec)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (exec->args[1] == NULL)
	{
		print_env(shell);
		return ;
	}
	while (exec->args[i])
	{
		key = ft_strdup(exec->args[i]);
		value = ft_strdup(exec->args[i]);
		if (ft_strchr(exec->args[i], '='))
		{
			key = ft_substr(exec->args[i], 0, ft_strchr(exec->args[i], '=')
					- exec->args[i]);
			value = ft_substr(exec->args[i], ft_strchr(exec->args[i], '=')
					- exec->args[i] + 1, ft_strlen(exec->args[i]));
		}
		if (get_env(shell, key) != NULL)
		{
			set_env(shell, key, value);
			free(key);
			free(value);
			i++;
			continue;
		}
		if (ft_isdigit(key[0]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", key);
			return ;
		}
		add_env(shell, key, value);
		free(key);
		free(value);
		i++;
	}
}
