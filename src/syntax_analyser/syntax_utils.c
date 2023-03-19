/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:18:52 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/19 18:20:21 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_redirection(int type)
{
	if (type == REDIR_OUT || type == REDIR_IN || type == HERDOC
		|| type == REDIR_APPEND)
		return (1);
	return (0);
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
		ft_putstr("minishell: unclosed ", STDERR_FILENO);
		if (type == SQUOTE)
			ft_putstr("single quotes detected.\n", STDERR_FILENO);
		else if (type == DQUOTE)
			ft_putstr("double quotes detected.\n", STDERR_FILENO);
		return (FAILURE);
	}
	*token = prev_tkn;
	return (SUCCESS);
}

int	pipe_err(t_token *token, t_token *prev_tkn)
{
	if (!prev_tkn || !token->next)
		ft_putstr("minishell: syntax error near unexpected token `|'\n" \
		, STDERR_FILENO);
	else if ((prev_tkn->type != CMD && prev_tkn->type != WC && prev_tkn->type \
			!= DQUOTE && prev_tkn->type != SQUOTE) || (token->next->type != CMD
			&& token->next->type != WC && token->next->type != SPACE_MS
			&& !is_redirection(token->next->type) && token->next->type != DQUOTE
			&& token->next->type != SQUOTE))
		ft_putstr("minishell: syntax error near unexpected token `|'\n" \
			, STDERR_FILENO);
	else
		return (SUCCESS);
	return (FAILURE);
}

int	redir_err(t_shell *shell, t_token *token)
{
	skip_space(&token);
	if (!token)
		ft_putstr("minishell: syntax error near unexpected" \
			"token `newline'\n", STDERR_FILENO);
	else if (token->type != CMD && token->type != DOLLAR
		&& token->type != DQUOTE && token->type != SQUOTE
		&& token->type != WC)
	{
		ft_putstr("minishell: syntax error near unexpected token `", \
						STDERR_FILENO);
		ft_putstr(token->content, STDERR_FILENO);
		ft_putstr("'\n", STDERR_FILENO);
	}
	else
	{
		if (token->type == DQUOTE || token->type == SQUOTE)
			shell->inside_quotes = WITH_DQUOTES;
		else
			shell->inside_quotes = WITHOUT_QUOTES;
		return (SUCCESS);
	}
	return (FAILURE);
}
