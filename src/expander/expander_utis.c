/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:18:45 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/24 15:56:22 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_join(char *tmp, char *value)
{
	char *tmp2;
	tmp2 = ft_strjoin(tmp, value);
	// free(tmp);
	return (tmp2);
}

char	*after_dollar(t_shell *shell, char *str, char *tmp)
{
	int i;
	char *value;
	
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[0]))
			i++;
		else if (str[0] == '?')
			i++;
		else if (str[0] != '?' && !ft_isdigit(str[0]))
		{
			value = expand_after_dollar(shell, str, i);
			tmp = ft_join(tmp, value);
			i += ft_strlen(value) + 1;
		}
		else
		{
			tmp = ft_join(tmp, ft_substr(str, i, 1));
			i++;
		}
	}
	return (tmp);
}

char	*delet_dquotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	j = 0;
	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] != '\"')
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*delet_squotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	j = 0;
	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (str[i])
		if (str[i] != '\'')
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}
