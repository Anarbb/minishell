/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/18 16:39:28 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_after_dollar(t_shell *shell, char *str, int i)
{
	int len;
	char *tmp;
	char *value;
	char **env;

	env = shell->env;
	len = ft_strlen(str) - 1;
	tmp = ft_substr(str, i, len);
	while (*env != NULL)
	{
		if (ft_strncmp(*env, tmp, len) == 0 && (*env)[len] == '=')
		{
			value = ft_strdup(*env + (len + 1));
			free(tmp);
			return (value);
		}
		env++;
	}
	free(tmp);
	return (NULL);
}

char	*ft_join(char *tmp, char *value)
{
	char *tmp2;

	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	tmp = tmp2;
	free(value);
	return (tmp);
}

char	*after_dollar(t_shell *shell, char *str, char *tmp)
{
	int i;
	char *value;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else if (str[i] == '$' && str[i + 1] == '?')
			i += 2;
		else if (str[i] == '$' && str[i + 1] != '\'' && str[i + 1] != '\"' && str[i + 1] != '\0' && str[i + 1] != ' ')
		{
			value = expand_after_dollar(shell, str, i + 1);
			if (value != NULL)
			{
				i += ft_strlen(value) + 1;
				tmp = ft_join(tmp, value);
			}
			else
				i++;
		}
		else
		{
			tmp = ft_join(tmp, ft_substr(str, i, 1));
			i++;
		}
	}
	printf("%s\n",tmp);
	return (tmp);
}

//str the whole word
char	*expander(t_shell *shell, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		if (str[i] && str[i] == '$' && str[i + 1] != '\0')
			tmp = after_dollar(shell, str, tmp);
		// tmp = delet_squotes(tmp);
		// tmp = delet_dquotes(tmp);
		i++;
	}
	return (tmp);
}
