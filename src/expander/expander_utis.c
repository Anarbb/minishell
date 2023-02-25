/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:18:45 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/25 21:54:48 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*expand_after_dollar(t_shell *shell, char *str, int *i, int j)
{
	char	*tmp;
	char	*tmp2;
	char	*value;
	char	**env;

	env = shell->tmp_env;
	j = *i;
	if (ft_isalpha(str[j++]) || str[j++] == '_')
		while (ft_isalnum(str[j]) || str[j] == '_')
			(j)++;
	tmp = ft_strndup(str, j);
	tmp2 = ft_substr(str, j, ft_strlen(str));
	while (*env != NULL)
	{
		if (ft_strncmp(*env, tmp, j) == 0 && (*env)[j] == '=')
		{
			value = ft_strdup(*env + (j + 1));
			free(tmp);
				tmp = ft_join(value, tmp2);
			return (tmp);
		}
		env++;
	}
	return (*i = j, ft_strdup(""));
}

char	*after_dollar(t_shell *shell, char *str, char *tmp, int i)
{
	int len;
	char *value;
	
	len = ft_strlen(str);
	if (ft_isdigit(str[i]))
		i++;
	else if (str[i] == '?')
	{
		tmp = ft_join(tmp, ft_itoa(shell->exit_status));
		i++;
	}
	while (i < len)
	{
		if (i == 0)
			return (value = expand_after_dollar(shell, str, &i, 0), ft_join(tmp, value));
		else
			tmp = ft_join(tmp, ft_substr(str, i, 1));
		i++;
	}
	return (tmp);
}