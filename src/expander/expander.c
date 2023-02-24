/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/24 16:37:22 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_after_dollar(t_shell *shell, char *str, int i)
{
	char *tmp;
	char *tmp2;
	char *value;
	char **env;

	env = shell->tmp_env;
	if (ft_isalpha(str[i++]) || str[i++] == '_')
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
	tmp = ft_strndup(str, i);
	tmp2 = ft_substr(str, i, ft_strlen(str));
	while (*env != NULL)
	{
		if (ft_strncmp(*env, tmp, i) == 0 && (*env)[i] == '=')
		{
			value = ft_strdup(*env + (i + 1));
			free(tmp);
			if (tmp2[0] == '$')
				tmp = ft_join(value, expand_after_dollar(shell, tmp2 + 1, 0));
			else
				tmp = ft_join(value, tmp2);
			return (tmp);
		}
		env++;
	}
	if (tmp2[0] == '$')
	{
		tmp = ft_join(ft_strdup(""), expand_after_dollar(shell, tmp2 + 1, 0));
		return (tmp);
	}
	return (ft_strdup(""));
}

char	*expander(t_shell *shell, t_token *token)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	t_token	*prev_tkn;

	i = 0;
	prev_tkn = token;
	tmp = ft_strdup("");
	tmp2 = ft_strdup("");
	while (token)
	{
		if (token->type == DQUOTE)
		{
			token = token->next;
			while (token && token->type != DQUOTE)
			{
				if (token->type == DOLLAR && token->next->type == CMD)
				{
					tmp = after_dollar(shell, token->next->content, tmp);
					token = token->next->next;
				}
				else
				{
					tmp = ft_join(tmp, token->content);
					token = token->next;
				}
			}
		}
		else
		{
			if (token->type == SQUOTE)
			{
				token = token->next;
				while (token && token->type != SQUOTE)
				{
					tmp = ft_join(tmp, token->content);
					token = token->next;
				}
			}
			else if (token->type == DOLLAR && token->next->type == CMD)
			{
				tmp = after_dollar(shell, token->next->content, tmp);
				token = token->next->next;
			}
			else if(token->type == CMD)
				tmp = ft_join(tmp, token->content);
		}
		if (token != NULL)
			token = token->next;
	}
	printf("****%s\n",tmp);
	return (tmp);
}
