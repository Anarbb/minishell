/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/21 15:16:20 by aarbaoui         ###   ########.fr       */
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
	else if (str[i] == '?')
	{
		tmp2 = ft_itoa(shell->exit_status);
		tmp = ft_join(tmp, tmp2);
		free(tmp2);
		i++;
	}
	while (i < len)
	{
		if (i == 0)
		{
			value = expand_after_dollar(shell, str, &i);
			tmp = ft_join(tmp, value);
			free(value);
		}
		else
		{
			tmp2 = ft_substr(str, i, 1);
			tmp = ft_join(tmp, tmp2);
			free(tmp2);
		}
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

char	*expand_cmd(t_token **token, t_shell *shell, t_token **new_tkn)
{
	char	*tmp;

	tmp = ft_strdup("");
	if ((*token)->type == WC)
		add_wc_tokens(expand_wildcard(new_tkn), new_tkn);
	else if ((*token)->next && (*token)->type == DOLLAR
			&& (*token)->next->type == CMD)
	{
		*token = (*token)->next;
		tmp = after_dollar(shell, (*token)->content, tmp, 0);
	}
	else if ((*token)->type == CMD || (*token)->type == DOLLAR)
		tmp = ft_join(tmp, (*token)->content);
	else
	{
		if ((*token)->type != SPACE_MS)
			tmp = ft_join(tmp, (*token)->content);
	}
	if (*tmp)
		return (tmp);
	free(tmp);
	return (NULL);
}


void	expander(t_shell *shell, t_token *token, t_token *new_tkn)
{
	char	*tmp;
	char	*expanded;
	t_token	*tmp_tkn;

	tmp = ft_strdup("");
	while (token)
	{
		if (!token)
			break ;
		if (token->next && token->type == CMD && (token->next->type == DQUOTE
				|| token->next->type == SQUOTE))
		{
			expanded = expand_cmd(&token, shell, &new_tkn);
			tmp = ft_join(tmp, expanded);
			if (expanded)
				free(expanded);
			token = token->next;
			if (token->type == DQUOTE)
			{
				expanded = expand_in_dquote(&token, shell, NULL);
				tmp = ft_join(tmp, expanded);
				if (expanded)
					free(expanded);
			}
			else if (token->type == SQUOTE)
			{
				expanded = expand_in_squote(&token);
				tmp = ft_join(tmp, expanded);
				if (expanded)
					free(expanded);
			}
			new_tkn = create_token(new_tkn, tmp, CMD);
			tmp = ft_strdup("");
		}
		else if (token->type == DQUOTE)
		{
			expanded = expand_in_dquote(&token, shell, NULL);
			tmp = ft_join(tmp, expanded);
			if (expanded)
				free(expanded);
			new_tkn = create_token(new_tkn, tmp, CMD);
			tmp = ft_strdup("");
			new_tkn->inside_quotes = WITH_DQUOTES;
		}
		else if (token->type == SQUOTE)
		{
			expanded = expand_in_squote(&token);
			tmp = ft_join(tmp, expanded);
			if (expanded)
				free(expanded);
			new_tkn = create_token(new_tkn, tmp, CMD);
			tmp = ft_strdup("");
			new_tkn->inside_quotes = WITH_SQUOTES;
		}
		else
		{
			expanded = expand_cmd(&token, shell, &new_tkn);
			if (expanded)
			{
				tmp = ft_join(tmp, expanded);
				free(expanded);
			}
			if (tmp[0] != '\0')
			{
				new_tkn = create_token(new_tkn, tmp, token->type);
				tmp = ft_strdup("");
			}
		}
		token = token->next;
	}
	tmp_tkn = shell->token;
	shell->token = new_tkn;
	free(tmp);
	free_tokens(&tmp_tkn);
}
