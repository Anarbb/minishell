/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:36 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/11 18:24:19 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *tmp, char *value)
{
	tmp = ft_strjoin(tmp, value);
	return (tmp);
}

void	expander(t_shell *shell, t_token *token)
{
	int		i;
	char	*tmp;
	t_token	*new_tkn;

	i = 0;
	new_tkn = NULL;
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
					token = token->next->next;
				}
				else
				{
					tmp = ft_join(tmp, token->content);
					token = token->next;
				}
			}
			if (token->type == DQUOTE)
			{
				new_tkn = create_token(new_tkn, tmp, CMD);
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
					token = token->next;
				}
				if (token->type == SQUOTE)
				{
					new_tkn = create_token(new_tkn, tmp, CMD);
					tmp = ft_strdup("");
					token = token->next;
				}
			}
			else if (token->type == DOLLAR && token->next->type == CMD)
			{
				tmp = after_dollar(shell, token->next->content, tmp, i);
				new_tkn = create_token(new_tkn, tmp, CMD);
				tmp = ft_strdup("");
				token = token->next->next;
			}
			else if (token->type == CMD)
			{
				tmp = ft_join(tmp, token->content);
				new_tkn = create_token(new_tkn, tmp, CMD);
				tmp = ft_strdup("");
				token = token->next;
			}
			else
			{
				if (token->type != SPACE_MS)
				{
					tmp = ft_join(tmp, token->content);
					new_tkn = create_token(new_tkn, tmp, token->type);
					tmp = ft_strdup("");
				}
				token = token->next;
			}
		}
	}
	shell->token = new_tkn;
	t_token *ptr = shell->token;
	while (ptr)
	{
		printf("content: %s, type: %d\n", ptr->content, ptr->type);
		ptr = ptr->next;
	}
}
