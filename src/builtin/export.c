/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/21 20:19:59 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str, int plus)
{
	int		i;
	char	*key;

	i = 0;
	if (plus)
		i = ft_strfind(str, '+');
	else
		i = ft_strfind(str, '=');
	if (i == -1)
		i = ft_strlen(str);
	key = ft_strndup(str, i);
	return (key);
}

char	*get_value(char *str)
{
	int		i;
	char	*value;

	i = ft_strfind(str, '=');
	if (i == -1)
		value = NULL;
	else
		value = ft_strdup(str + i + 1);
	return (value);
}

void	export_env(char *str, t_shell *shell, int plus, char *tmp)
{
	char	*key;
	char	*value;

	key = get_key(str, plus);
	value = get_value(str);
	if (check_key_exists(key, shell))
	{
		if (plus)
		{
			tmp = append_to_var(get_env(shell, key), value);
			set_env(shell, key, tmp, 1);
			free(tmp);
		}
		else
			set_env(shell, key, value, 1);
	}
	else
	{
		if (plus)
			add_env(shell, key, value, 1);
		else
			add_env(shell, key, value, 1);
	}
	free(value);
	free(key);
}

void	handle_invalid_identifier(t_shell *shell, char *arg, int *i)
{
	shell->exit_status = 1;
	printf("minishell: export: `%s': not a valid identifier\n", arg);
	(*i)++;
}

int	ft_export(t_shell *shell, t_exec *exec, int plus, int i)
{
	char	*key;
	char	*value;

	if (exec->args[i] == NULL)
	{
		print_env(shell);
		return (shell->exit_status = 0, 1);
	}
	while (exec->args[i])
	{
		if (is_invalid_identifier(exec->args[i]))
		{
			handle_invalid_identifier(shell, exec->args[i], &i);
			continue ;
		}
		if (has_plus(exec->args[i]))
			plus = 1;
		key = get_key(exec->args[i], plus);
		value = get_value(exec->args[i]);
		export_env(exec->args[i], shell, plus, NULL);
		free(key);
		free(value);
		i++;
	}
	return (shell->exit_status = 0, 1);
}
