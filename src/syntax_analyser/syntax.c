/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:47:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/21 14:40:53 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(t_token **token)
{
	if (*token && (*token)->type == SPACE_MS)
		while (*token && (*token)->type == SPACE_MS)
			*token = (*token)->next;
	return (1);
}

int	inred_outred(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if ((*token)->type == REDIR_IN && (*token)->next
		&& (*token)->next->type == REDIR_OUT)
	{
		current = (*token)->next;
		next = current->next;
		free(current->content);
		free(current);
		(*token)->next = next;
		return (1);
	}
	return (1);
}

int	validate_syntax(t_shell *shell, t_token *token, t_token *prev_tkn)
{
	while (token)
	{
		skip_space(&token);
		if (!token)
			break ;
		if (token->type == PIPE)
		{
			if (pipe_err(token, prev_tkn))
				return (FAILURE);
		}
		else if (token->type == DQUOTE || token->type == SQUOTE)
		{
			if (unclosed_err(&token, token->type, prev_tkn) == FAILURE)
				return (FAILURE);
		}
		else if (is_redirection(token->type))
		{
			if (inred_outred(&token))
				if (redir_err(shell, token->next) == FAILURE)
					return (FAILURE);
		}
		prev_tkn = token;
		token = token->next;
	}
	return (SUCCESS);
}
