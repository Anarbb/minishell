/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/19 22:40:33 by lsabik           ###   ########.fr       */
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

	len = ft_strlen(str);
	if (ft_isdigit(str[i]))
		i++;
	else if (str[i] == '?')
	{
		tmp = ft_join(tmp, ft_itoa((uint8_t)shell->exit_status));
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
			tmp = ft_join(tmp, ft_substr(str, i, 1));
		i++;
	}
	return (tmp);
}

void	expand_wildcard(t_token **new_tkn)
{
	DIR				*dirp;
	struct dirent	*direc_p;
	char			*tmp;
	char			*path;

	path = getcwd(NULL, 0);
	dirp = opendir(path);
	tmp = NULL;
	while (get_file_path(&direc_p, &dirp))
	{
		if (ft_strncmp(direc_p->d_name, ".", 1) == 0)
			continue ;
		tmp = ft_strdup(direc_p->d_name);
		if (tmp == NULL)
			alloc_error();
		*new_tkn = create_token(*new_tkn, tmp, CMD);
		if (*new_tkn == NULL)
			alloc_error();
	}
	free(path);
	closedir(dirp);
}

char	*expand_cmd(t_token **token, t_shell *shell, t_token **new_tkn)
{
	char	*tmp;

	tmp = ft_strdup("");
	if ((*token)->type == WC)
		expand_wildcard(new_tkn);
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
	return (tmp);
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
			tmp = ft_join(tmp, expanded);
			if (expanded)
				free(expanded);
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
