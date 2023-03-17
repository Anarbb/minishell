/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:47:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/17 20:52:27 by aarbaoui         ###   ########.fr       */
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

int	unclosed_err(t_token **token, int type, t_token *prev_tkn)
{
	int	count;

	count = 0;
	prev_tkn = *token;
	while (*token && count != 2)
	{
		if ((*token)->type == type)
			count++;
		prev_tkn = *token;
		*token = (*token)->next;
	}
	if (count % 2 != 0)
	{
		ft_putstr_fd("minishell: unclosed ", STDERR_FILENO);
		if (type == SQUOTE)
			ft_putstr_fd("single quotes detected.\n", STDERR_FILENO);
		else if (type == DQUOTE)
			ft_putstr_fd("double quotes detected.\n", STDERR_FILENO);
		return (FAILURE);
	}
	*token = prev_tkn;
	return (SUCCESS);
}

int	pipe_err(t_token *token, t_token *prev_tkn)
{
	if (!prev_tkn || !token->next)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n" \
		, STDERR_FILENO);
	else if ((prev_tkn->type != CMD && prev_tkn->type != WC)
		|| (token->next->type != CMD && token->next->type != WC \
		&& token->next->type != SPACE_MS && !is_redirection(token->next->type)))
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n" \
			, STDERR_FILENO);
	else
		return (SUCCESS);
	return (FAILURE);
}

int	redir_err(t_shell *shell, t_token *token)
{
	skip_space(&token);
	if (token->type == DQUOTE || token->type == SQUOTE)
		shell->inside_quotes = WITH_QUOTES;
	if (!token)
		ft_putstr_fd("minishell: syntax error near unexpected \
			token `newline'\n", STDERR_FILENO);
	else if (token->type != CMD && token->type != DOLLAR
		&& token->type != DQUOTE && token->type != SQUOTE
		&& token->type != WC)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", \
						STDERR_FILENO);
		ft_putstr_fd(token->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else
		return (SUCCESS);
	return (FAILURE);
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
			if (redir_err(shell, token->next) == FAILURE)
				return (FAILURE);
		}
		prev_tkn = token;
		token = token->next;
	}
	return (SUCCESS);
}
