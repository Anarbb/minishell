/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:18:45 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/18 22:48:31 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_after_dollar(t_shell *shell, char *str, int *i)
{
	char	*value;
	char	*tmp;

	tmp = ft_strdup("");
	while (str[*i] && ft_isalnum(str[*i]))
	{
		tmp = ft_join(tmp, ft_substr(str, *i, 1));
		(*i)++;
	}
	if (ft_strlen(tmp) == 0)
		return (tmp);
	value = get_env(shell, tmp);
	if (value == NULL)
		return (ft_strdup(""));
	else
	{
		tmp = ft_strdup(value);
		return (tmp);
	}
}

char	*expand_in_dquote(t_token **token, t_shell *shell)
{
	char	*tmp;

	tmp = ft_strdup("");
	*token = (*token)->next;
	while (*token && (*token)->type != DQUOTE)
	{
		if ((*token)->type == DOLLAR && (*token)->next->type == CMD)
		{
			*token = (*token)->next;
			tmp = after_dollar(shell, (*token)->content, tmp, 0);
		}
		else
			tmp = ft_join(tmp, (*token)->content);
		*token = (*token)->next;
	}
	if ((*token)->type == DQUOTE)
	{
		if ((*token)->next)
		{
			if ((*token)->next->type == CMD)
			{
				*token = (*token)->next;
				tmp = ft_join(tmp, (*token)->content);
			}
		}
	}
	return (tmp);
}

char	*expand_in_squote(t_token **token)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	*token = (*token)->next;
	while (*token && (*token)->type != SQUOTE)
	{
		tmp = ft_join(tmp, (*token)->content);
		*token = (*token)->next;
	}
	if ((*token)->type == SQUOTE)
	{
		if ((*token)->next)
		{
			if ((*token)->next->type == CMD)
			{
				*token = (*token)->next;
				tmp = ft_join(tmp, (*token)->content);
			}
		}
	}
	return (tmp);
}
