/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:07:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/21 00:04:38 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && (str[i] != '=' || str[i] != '+'))
		i++;
	key = ft_strndup(str, i);
	return (key);
}

char	*get_value(char *str)
{
	int		i;
	char	*value;

	i = ft_strfind(str, '=');
	if (i == -1)
		value = ft_strdup("");
	else
		value = ft_strdup(str + i + 1);
	return (value);
}

void	export_env(char *str, t_shell *shell, int plus)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = get_key(str);
	value = get_value(str);
	if (get_env(shell, key))
	{
		if (plus)
		{
			tmp = append_to_var(get_env(shell, key), value);
			set_env(shell, key, tmp);
			free(tmp);
		}
		else
			set_env(shell, key, value);
	}
	else
	{
		if (plus)
			add_env(shell, key, value);
		else
			add_env(shell, key, value);
	}
	free(key);
	// free(value);
}

void	ft_export(t_shell *shell, t_exec *exec, int plus, int i)
{
	char	*key;
	char	*value;

	if (exec->args[i] == NULL)
	{
		print_env(shell);
		shell->exit_status = 0;
		return ;
	}
	while (exec->args[i])
	{
		// if (is_invalid_identifier(exec->args[i]))
		// {
		// 	shell->exit_status = 1;
		// 	printf("minishell: export: `%s': not a valid identifier\n",
		// 		exec->args[i]);
		// 	i++;
		// 	continue ;
		// }
		if (has_plus(exec->args[i]))
			plus = 1;
		key = get_key(exec->args[i]);
		value = get_value(exec->args[i]);
		if (!value)
			value = "";
		export_env(exec->args[i], shell, plus);
		i++;
	}
	shell->exit_status = 0;
}

// void	handle_invalid_identifier(t_shell *shell, char *arg)
// {
// 	shell->exit_status = 1;
// 	printf("minishell: export: `%s': not a valid identifier\n", arg);
// }

// void	handle_plus(t_shell *shell, int plus, char *key, char *value)
// {
// 	if (plus)
// 		set_env(shell, key, append_to_var(get_env(shell, key), value));
// 	else
// 		add_env(shell, key, value);
// 	free(key);
// }

// void	process_export_argument(t_shell *shell, int *i, int plus, char *arg)
// {
// 	char	*key;
// 	char	*value;

// 	if (!plus)
// 		key = ft_strndup(arg, ft_strchr(arg, '=') - arg);
// 	else
// 		key = ft_strndup(arg, ft_strchr(arg, '+') - arg);
// 	value = ft_strchr(arg, '=') + 1;
// 	if (get_env(shell, key) && !plus)
// 	{
// 		set_env(shell, key, value);
// 		free(key);
// 	}
// 	else
// 	{
// 		if (get_env(shell, key))
// 			set_env(shell, key, append_to_var(get_env(shell, key), value));
// 		else
// 			add_env(shell, key, value);
// 		free(key);
// 	}
// 	handle_plus(shell, plus, key, value);
// }

// void	ft_export(t_shell *shell, t_exec *exec, int plus, int i)
// {
// 	int	flag;

// 	flag = 1;
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
// 			handle_invalid_identifier(shell, exec->args[i]);
// 			i++;
// 			continue ;
// 		}
// 		else
// 		{
// 			if (has_plus(exec->args[i]))
// 				plus = 1;
// 			process_export_argument(shell, &i, plus, exec->args[i]);
// 		}
// 		i++;
// 	}
// 	shell->exit_status = 0;
// }
