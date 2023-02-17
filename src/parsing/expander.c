/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/17 16:00:37 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_after_dollar(t_shell *shell, char *str, int i)
{
	int		j;
	int		len;
	char	*tmp;
	char	**env;
	// char	*tmp1;

	j = 0;
	env = shell->env;
	len = ft_strlen(str) - 1;
	tmp = ft_substr(str, i, len);
	while (ft_strncmp(*env, tmp, len) != 0)
		env++;
	tmp = (*env + (len + 1));
	printf("%s, len :%d\n",tmp, len);
	// printf("%s\n",tmp1);
	return (tmp);
}

void	after_dollar(t_shell *shell, char *str)
{
	int 	i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else if (str[i] == '$' && str[i + 1] == '?')
			shell->exit_status = 0;
		else if (str[i] == '$' && str[i + 1] != '\'' && str[i + 1] != '\"' && str[i + 1] != '\0' && str[i + 1] != ' ')
			tmp = expand_after_dollar(shell, str, i + 1);
		// else
		// {
			
		// }
		i++;
	}
}
//str the whole word
char	*expander(t_shell *shell, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '$' && str[i + 1] != '\0')
		{
			after_dollar(shell, str);
		}
		// delet_dquotes();
		// delet_squotes();
		i++;
	}
	return (NULL);
}