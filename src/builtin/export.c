/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 13:03:00 by aarbaoui         ###   ########.fr       */
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

int	has_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*append_to_var(char *var, char *value)
{
	char	*tmp;

	tmp = ft_strjoin(var, value);
	free(var);
	return (tmp);
}

int is_invalid_identifier(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=' && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

void	ft_export(t_shell *shell, t_exec *exec)
{
	int		i;
	char	*key;
	char	*value;
	int		plus;

	plus = 0;
	i = 1;
	if (exec->args[i] == NULL)
	{
		print_env(shell);
		shell->exit_status = 0;
		return ;
	}
	while (exec->args[i])
	{
		if (is_invalid_identifier(exec->args[i]))
		{
			shell->exit_status = 1;
			printf("minishell: export: `%s': not a valid identifier\n",
					exec->args[i]);
			i++;
			continue ;
		}
		if (has_plus(exec->args[i]))
			plus = 1;
		if (!plus)
			key = ft_strndup(exec->args[i], ft_strchr(exec->args[i], '=')
					- exec->args[i]);
		else
			key = ft_strndup(exec->args[i], ft_strchr(exec->args[i], '+')
					- exec->args[i]);
		value = ft_strchr(exec->args[i], '=') + 1;
		if (get_env(shell, key) && !plus)
		{
			set_env(shell, key, value);
			free(key);
			i++;
			continue ;
		}
		else
		{
			if (get_env(shell, key))
				set_env(shell, key, append_to_var(get_env(shell, key), value));
			else
				add_env(shell, key, value);
			i++;
			free(key);
			continue ;
		}
		if (plus)
			set_env(shell, key, append_to_var(get_env(shell, key), value));
		else
			add_env(shell, key, value);
		free(key);
		i++;
	}
	shell->exit_status = 0;
}
