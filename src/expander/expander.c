/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/02 17:20:36 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *tmp, char *value)
{
	tmp = ft_strjoin(tmp, value);
	return (tmp);
}

char	*expander(t_shell *shell, t_token *token)
{
	int		i;
	char	*tmp;
	t_token	*prev_tkn;

	i = 0;
	prev_tkn = token;
	tmp = ft_strdup("");
	while (token)
	{
		if (token->type == DQUOTE)
		{
			token = token->next;
			while (token && token->type != DQUOTE)
			{
				if (token->type == DOLLAR && token->next->type == CMD)
				{
					tmp = after_dollar(shell, token->next->content, tmp, i);
					exec_create(shell, tmp, token->next->type);
					tmp = ft_strdup("");
					token = token->next->next;
				}
				else
				{
					if (token->next && token->next->type != DQUOTE)
						tmp = ft_join(tmp, ft_join(token->content, " "));
					else
						tmp = ft_join(tmp, token->content);
					token = token->next;
				}
			}
			if (token->type == DQUOTE)
			{
				exec_create(shell, tmp, token->type);
				token = token->next;
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
					exec_create(shell, tmp, token->type);
					tmp = ft_strdup("");
					token = token->next;
				}
				if (token->type == SQUOTE)
					token = token->next;
			}
			else if (token->type == DOLLAR && token->next->type == CMD)
			{
				tmp = after_dollar(shell, token->next->content, tmp, i);
				exec_create(shell, tmp, token->type);
				tmp = ft_strdup("");
				token = token->next->next;
			}
			else if (token->type == CMD)
			{
				tmp = ft_join(tmp, token->content);
				exec_create(shell, tmp, token->type);
				tmp = ft_strdup("");
				token = token->next;
			}
			else
			{
				tmp = ft_join(tmp, token->content);
				exec_create(shell, tmp, token->type);
				tmp = ft_strdup("");
				token = token->next;
			}
		}
	}
	return (tmp);
}
