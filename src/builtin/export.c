/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/20 13:09:25 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	is_invalid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=' \
			&& str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

// void	ft_export(t_shell *shell, t_exec *exec, int plus, int i)
// {
// 	char	*key;
// 	char	*value;

// 	if (exec->args[i] == NULL)
// 	{
// 		print_env(shell);
// 		shell->exit_status = 0;
// 		return ;
// 	}
// 	while (exec->args[i])
// 	{
// 		if (is_invalid_identifier(exec->args[i]))
// 		{
// 			shell->exit_status = 1;
// 			printf("minishell: export: `%s': not a valid identifier\n",
// 				exec->args[i]);
// 			i++;
// 			continue ;
// 		}
// 		if (has_plus(exec->args[i]))
// 			plus = 1;
// 		if (!plus)
// 			key = ft_strndup(exec->args[i], ft_strchr(exec->args[i], '=')
// 					- exec->args[i]);
// 		else
// 			key = ft_strndup(exec->args[i], ft_strchr(exec->args[i], '+')
// 					- exec->args[i]);
// 		value = ft_strchr(exec->args[i], '=') + 1;
// 		if (get_env(shell, key) && !plus)
// 		{
// 			set_env(shell, key, value);
// 			free(key);
// 			i++;
// 			continue ;
// 		}
// 		else
// 		{
// 			if (get_env(shell, key))
// 				set_env(shell, key, append_to_var(get_env(shell, key), value));
// 			else
// 				add_env(shell, key, value);
// 			i++;
// 			free(key);
// 			continue ;
// 		}
// 		if (plus)
// 			set_env(shell, key, append_to_var(get_env(shell, key), value));
// 		else
// 			add_env(shell, key, value);
// 		free(key);
// 		i++;
// 	}
// 	shell->exit_status = 0;
// }

void handle_invalid_identifier(t_shell *shell, char *arg, int *i)
{
	shell->exit_status = 1;
	printf("minishell: export: `%s': not a valid identifier\n", arg);
	(*i)++;
}

void	handle_plus(t_shell *shell, int plus, char *key, char *value)
{
	if (plus)
		set_env(shell, key, append_to_var(get_env(shell, key), value));
	else
		add_env(shell, key, value);
	free(key);
}

void process_export_argument(t_shell *shell, int *i, int plus, char *arg)
{
	char	*key;
	char	*value;

	if (!plus)
		key = ft_strndup(arg, ft_strchr(arg, '=') - arg);
	else
		key = ft_strndup(arg, ft_strchr(arg, '+') - arg);
	value = ft_strchr(arg, '=') + 1;
	if (get_env(shell, key) && !plus)
	{
		set_env(shell, key, value);
		free(key);
		(*i)++;
	}
	else
	{
		if (get_env(shell, key))
			set_env(shell, key, append_to_var(get_env(shell, key), value));
		else
			add_env(shell, key, value);
		(*i)++;
		free(key);
	}
	handle_plus(shell, plus, key, value);
}

void	ft_export(t_shell *shell, t_exec *exec, int plus, int i)
{
	if (exec->args[i] == NULL)
	{
		print_env(shell);
		shell->exit_status = 0;
		return ;
	}
	while (exec->args[i])
	{
		if (is_invalid_identifier(exec->args[i]))
			handle_invalid_identifier(shell, exec->args[i], &i);
		if (has_plus(exec->args[i]))
			plus = 1;
		process_export_argument(shell, &i, plus, exec->args[i]);
		i++;
	}
	shell->exit_status = 0;
}
