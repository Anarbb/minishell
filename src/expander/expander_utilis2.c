/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utilis2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:35:47 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/21 19:40:11 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	after_dollar2(t_token **token, t_shell *shell, char **tmp)
{
	if ((*token)->next && (*token)->next->next && \
		(*token)->next->type == DOLLAR && (*token)->next->next->type == CMD)
	{
		*token = (*token)->next->next;
		*tmp = after_dollar(shell, (*token)->content, *tmp, 0);
	}
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
		after_dollar2(token, shell, &tmp);
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

void	quotes_after_cmd(t_token **token, t_shell *shell, t_token **new_tkn, \
		char **expanded)
{
	*expanded = expand_cmd(token, shell, new_tkn);
	shell->tmp = ft_join(shell->tmp, *expanded);
	if (*expanded)
		free(*expanded);
	*token = (*token)->next;
	if ((*token)->type == DQUOTE)
	{
		*expanded = expand_in_dquote(token, shell, NULL);
		shell->tmp = ft_join(shell->tmp, *expanded);
		if (*expanded)
			free(*expanded);
	}
	else if ((*token)->type == SQUOTE)
	{
		*expanded = expand_in_squote(token);
		shell->tmp = ft_join(shell->tmp, *expanded);
		if (*expanded)
			free(*expanded);
	}
	*new_tkn = create_token(*new_tkn, shell->tmp, CMD);
	shell->tmp = ft_strdup("");
}

void	join_quotes(t_token **new_tkn, t_shell *shell, char **expanded, \
		int join)
{
	shell->tmp = ft_join(shell->tmp, *expanded);
	if (*expanded)
		free(*expanded);
	*new_tkn = create_token(*new_tkn, shell->tmp, CMD);
	shell->tmp = ft_strdup("");
	if (join == WITH_DQUOTES)
		(*new_tkn)->inside_quotes = WITH_DQUOTES;
	else
		(*new_tkn)->inside_quotes = WITH_SQUOTES;
}

void	join_cmd(t_shell *shell, t_token **token, t_token **new_tkn, \
		char **expanded)
{
	*expanded = expand_cmd(token, shell, new_tkn);
	if (*expanded)
	{
		shell->tmp = ft_join(shell->tmp, *expanded);
		free(*expanded);
	}
	if (shell->tmp[0] != '\0')
	{
		*new_tkn = create_token(*new_tkn, shell->tmp, (*token)->type);
		shell->tmp = ft_strdup("");
	}
}
