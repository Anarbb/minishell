/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/21 15:41:55 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *tmp, char *value)
{
	char	*tmp2;

	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	return (tmp2);
}

char	*after_dollar(t_shell *shell, char *str, char *tmp, int i)
{
	int		len;
	char	*value;
	char	*tmp2;

	len = ft_strlen(str);
	if (ft_isdigit(str[i]))
		i++;
	if (str[i] == '?')
	{
		question_mark(&tmp2, &tmp, shell);
		i++;
	}
	while (i < len)
	{
		if (i == 0 || (str[i] == '$' && ft_isalnum(str[i + 1])))
		{
			value = expand_after_dollar(shell, str, &i);
			tmp = ft_join(tmp, value);
			free(value);
		}
		else
			tmp = ft_join(tmp, ft_substr(str, i, 1));
		i++;
	}
	return (tmp);
}

char	*expand_wildcard(t_token **new_tkn)
{
	DIR				*dirp;
	struct dirent	*direc_p;
	char			*tmp;
	char			*return_value;

	dirp = opendir(".");
	tmp = ft_strdup("");
	return_value = NULL;
	if (!dirp)
		return (tmp);
	while (get_file_path(&direc_p, &dirp))
	{
		if (ft_strncmp(direc_p->d_name, ".", 1) == 0)
			continue ;
		tmp = ft_join(tmp, direc_p->d_name);
		tmp = ft_join(tmp, " ");
	}
	if (tmp[0] == '\0')
		tmp = ft_strjoin(tmp, (*new_tkn)->content);
	closedir(dirp);
	return_value = ft_strdup(tmp);
	free(tmp);
	return (return_value);
}

void	add_wc_tokens(char *tmp, t_token **new_tkn)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(tmp, ' ');
	while (arr[i])
	{
		create_token(*new_tkn, arr[i], CMD);
		i++;
	}
	free(tmp);
	free(arr);
}

void	expander(t_shell *shell, t_token *token, t_token *new_tkn, \
		char *expanded)
{
	shell->tmp = ft_strdup("");
	while (token)
	{
		if (!token)
			break ;
		if (token->next && token->type == CMD && (token->next->type == DQUOTE \
			|| token->next->type == SQUOTE))
			quotes_after_cmd(&token, shell, &new_tkn, &expanded);
		else if (token->type == DQUOTE)
		{
			expanded = expand_in_dquote(&token, shell, NULL);
			join_quotes(&new_tkn, shell, &expanded, WITH_DQUOTES);
		}
		else if (token->type == SQUOTE)
		{
			expanded = expand_in_squote(&token);
			join_quotes(&new_tkn, shell, &expanded, WITH_SQUOTES);
		}
		else
			join_cmd(shell, &token, &new_tkn, &expanded);
		token = token->next;
	}
	free_in_expander(shell, &new_tkn);
}
