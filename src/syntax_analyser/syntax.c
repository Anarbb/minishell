/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:47:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/17 15:09:56 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	unclosed_err(t_token **token, int type)
{
	int	count = 0;
	while (*token)
	{
		if ((*token)->type == type)
		{
			if (++count && (*token)->content && (*token)->content[0] == type)
				while (*token && --count)
					*token = (*token)->next;
			else
				while (*token && --count >= 0)
					*token = (*token)->next;
			if (count < 0)
			{
				ft_putstr_fd("minishell: unclosed ", STDERR_FILENO);
				if (type == SQUOTE)
					ft_putstr_fd("single quotes detected.\n", STDERR_FILENO);
				else if (type == DQUOTE)
					ft_putstr_fd("double quotes detected.\n", STDERR_FILENO);
				return (FAILURE);
			}
		}
		*token = (*token)->next;
	}
	return (SUCCESS);
}

int	pipe_err(t_token *token, t_token *prev_tkn)
{
    if (!prev_tkn || !token->next)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
    else if (prev_tkn->type != CMD || (token->next->type != CMD 
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
	else if (token->next->type != CMD && token->next->type != DOLLAR)
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
		else if (token->type == SQUOTE || token->type == DQUOTE)
		{
			if (unclosed_err(&token, token->type) == FAILURE)
				return (FAILURE);
		}
		else if (is_redirection(token->type))
		{
			if (redir_err(token) == FAILURE)
				return (FAILURE);
		}
		token = token->next;
	}
	return (SUCCESS);
}
