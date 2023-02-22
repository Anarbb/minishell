/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/21 15:23:51 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_after_dollar(t_shell *shell, char *str, int i)
{
	int len;
	char *tmp;
	char *value;
	char **env;

	env = shell->tmp_env;
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
	return (0);
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
		else if (str[i] == '$' && str[i + 1] != '\0')
		{
			value = expand_after_dollar(shell, str, i + 1);
			if (value != NULL)
				tmp = ft_join(tmp, value);
			i += ft_strlen(str) + 1;
		}
		else
		{
			tmp = ft_join(tmp, ft_substr(str, i, 1));
			i++;
		}
	}
	return (tmp);
}

int	check_dollar(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*expander(t_shell *shell, t_token *token)
{
	int		i;
	char	*tmp;
	t_token	*prev_tkn;

	prev_tkn = token;
	i = 0;
	tmp = ft_strdup("");
	while (token)
	{
		if (token && prev_tkn->type != SQUOTE && token->type == CMD  && check_dollar(token->content, '$'))
			tmp = after_dollar(shell, token->content, tmp);
		else
		{
			if (prev_tkn->type != SQUOTE && token->type != DQUOTE && token->type != DOLLAR)
				tmp = ft_join(tmp, ft_strdup(token->content));
			else
				tmp = ft_join(tmp, ft_substr(token->content, i, ft_strlen(token->content)));
		
		}
		prev_tkn = token;
		token = token->next;
	}
		// tmp = delet_squotes(tmp);
		tmp = delet_dquotes(tmp);
	return (tmp);
}
