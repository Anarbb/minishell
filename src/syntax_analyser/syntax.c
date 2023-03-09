/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:47:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/09 13:46:09 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


int unclosed_err(t_token **token, int type, t_token *prev_tkn)
{
    int		count;

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
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
    else if (prev_tkn->type != CMD || (token->next->type != CMD 
			&& token->next->type != SPACE_MS
			&& !is_redirection(token->next->type)))
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
	else
		return (SUCCESS);
	return (FAILURE);
}

int	redir_err(t_token *token)
{
    if (!(token->next))
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
	else if (token->next->type != CMD && token->next->type != DOLLAR
			&& token->next->type != SPACE_MS)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token->next->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else
		return (SUCCESS);
	return (FAILURE);
}

int	validate_syntax(t_token *token)
{
	t_token	*prev_tkn;

	prev_tkn = token;
	while (token)
	{
		if (token->type == PIPE)
		{
			if (pipe_err(token, prev_tkn))
				return (FAILURE);
		}
		else if (token->type == DQUOTE)
		{
			if (unclosed_err(&token, token->type, prev_tkn) == FAILURE)
				return (FAILURE);
		}
		else if (token->type == SQUOTE)
		{
			if (unclosed_err(&token, token->type, prev_tkn) == FAILURE)
				return (FAILURE);
		}
		else if (is_redirection(token->type))
		{
			if (redir_err(token) == FAILURE)
				return (FAILURE);
		}
		if (token != NULL)
			token = token->next;
	}
	return (SUCCESS);
}
