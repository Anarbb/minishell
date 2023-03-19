/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/19 09:42:50 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *tmp, char *value)
{
	tmp = ft_strjoin(tmp, value);
	return (tmp);
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
			return (value = expand_after_dollar(shell, str, &i) \
				, ft_join(tmp, value));
		else
			tmp = ft_join(tmp, ft_substr(str, i, 1));
		i++;
	}
	return (tmp);
}

void	expand_wildcard(t_token **new_tkn, char *tmp)
{
	DIR				*dirp;
	struct dirent	*direc_p;

	dirp = opendir(getcwd(NULL, 0));
	while ((direc_p = readdir(dirp)) != NULL)
	{
		if (ft_strncmp(direc_p->d_name, ".", 1))
		{
			tmp = ft_join(tmp, direc_p->d_name);
			*new_tkn = create_token(*new_tkn, tmp, CMD);
			tmp = NULL;
			tmp = ft_strdup("");
		}
	}
	closedir(dirp);
}

char	*expand_cmd(t_token **token, t_shell *shell, t_token **new_tkn)
{
	char	*tmp;
	
	tmp = ft_strdup("");
	if ((*token)->type == WC)
		expand_wildcard(new_tkn, tmp);
		
	else if ((*token)->next && (*token)->type == DOLLAR && (*token)->next->type == CMD)
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

void	expander(t_shell *shell, t_token *token)
{
	t_token	*new_tkn;
	char	*tmp;

	tmp = ft_strdup("");
	new_tkn = NULL;
	while (token)
	{
		if (!token)
			break;
		if (token->next && token->type == CMD && token->next->type == DQUOTE)
		{
			tmp = ft_strjoin(tmp, expand_cmd(&token, shell, &new_tkn));
			token = token->next;
			tmp = ft_strjoin(tmp, expand_in_dquote(&token, shell));
			new_tkn = create_token(new_tkn, tmp, CMD);
			tmp =	ft_strdup("");
			
		}
		else if (token->type == DQUOTE)
		{
			tmp = ft_strjoin(tmp, expand_in_dquote(&token, shell));
			new_tkn = create_token(new_tkn, tmp, CMD);
			tmp =	ft_strdup("");
			new_tkn->inside_quotes = WITH_DQUOTES;
		}
		else
		{
			if (token->type == SQUOTE)
			{
				tmp = ft_strjoin(tmp, expand_in_squote(&token));
				new_tkn = create_token(new_tkn, tmp, CMD);
				tmp =	ft_strdup("");
				new_tkn->inside_quotes = WITH_SQUOTES;
			}
			else
			{
				tmp = ft_strjoin(tmp, expand_cmd(&token, shell, &new_tkn));
				if (tmp[0] != '\0')
					new_tkn = create_token(new_tkn, tmp, token->type);
				tmp = ft_strdup("");
			}
			
		}
		token = token->next;
	}
	free(shell->token);
	shell->token = new_tkn;
}
