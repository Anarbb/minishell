/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:47:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/09 20:00:23 by lsabik           ###   ########.fr       */
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

void	skip_space(t_token **token)
{
	if ((*token)->type == SPACE_MS)
		while ((*token)->type == SPACE_MS)
			*token = (*token)->next;
}

int	redir_err(t_token *token)
{
    if (!token)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
	else if (token->next->type != CMD && token->next->type != DOLLAR)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token->content, STDERR_FILENO);
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
			if (redir_err(token->next) == FAILURE)
				return (FAILURE);
		}
		if (token != NULL)
			token = token->next;
	}
	return (SUCCESS);
}
