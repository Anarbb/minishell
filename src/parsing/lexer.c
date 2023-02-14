/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/13 17:10:24 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_new_token(char *str, int len, int type)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	token->content = ft_substr(str, 0, len);
	token->type = type;
	token->next = NULL;
	return (token);
}

static int ft_is_in(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int ft_lexer(t_shell *shell)
{
	char token_chars[] = {' ', '>', '<', '|', ';', '(', ')'};
	int token_types[] = {EMPTY, REDIRECTION, REDIRECTION, PIPE, AND, PARENTHESE_OPEN, PARENTHESE_CLOSE};
	int i;
	int j;
	int len;
	char *str;
	t_token *token;

	i = 0;
	j = 0;
	len = 0;
	str = shell->line;
	while (str[i])
	{
		while (str[i] && !ft_is_in(token_chars, str[i]))
		{
			i++;
			len++;
		}
		if (len > 0)
		{
			token = ft_new_token(str, len, EMPTY);
			ft_token_add_back(&shell->token, token);
		}
		len = 0;
		while (str[i] && ft_is_in(token_chars, str[i]))
		{
			i++;
			len++;
		}
		if (len > 0)
		{
			while (j < 7 && str[i - len] != token_chars[j])
				j++;
			token = ft_new_token(str, len, token_types[j]);
			ft_token_add_back(&shell->token, token);
			j = 0;
		}
		len = 0;
	}
	return (1);
}

