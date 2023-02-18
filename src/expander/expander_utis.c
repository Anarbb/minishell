/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:18:45 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/18 21:31:07 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_join(char *tmp, char *value)
{
	char *tmp2;

	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	tmp = tmp2;
	free(value);
	return (tmp);
}

char	*delet_dquotes(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\"')
		{
			*new_str = str[i];
			new_str++;
		}
		i++;
	}
	*new_str = '\0';
	str = new_str;
	return (str);
}

char	*delet_squotes(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'')
		{
			*new_str = str[i];
			new_str++;
		}
		i++;
	}
	*new_str = '\0';
	str = new_str;
	return (str);
}
