/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:47:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/02/14 21:47:01 by lsabik           ###   ########.fr       */
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
				if (type == SINGLE_QUOTE)
					ft_putstr_fd("single quotes detected.\n", STDERR_FILENO);
				else if (type == DOUBLE_QUOTE)
					ft_putstr_fd("double quotes detected.\n", STDERR_FILENO);
				else
					ft_putstr_fd("parentheses detected.\n", STDERR_FILENO);
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
    else if (prev_tkn->type != CMD || (token->next->type != CMD && token->next->type != REDIR))
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
	else
		return (SUCCESS);
	return (FAILURE);
}

int	redir_err(t_token *token)
{
    if (!(token->next))
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'", STDERR_FILENO);
	else if (token->next->type != CMD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token->next->content, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
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
		if (token->type == PARENTHESIS)
		{
			if (unclosed_err(&token, token->type) == FAILURE)
				return (FAILURE);	
		}
		else if (token->type == PIPE)
		{
			if (pipe_err(token, prev_tkn))
				return (FAILURE);
		}
		else if (token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		{
			if (unclosed_err(&token, token->type) == FAILURE)
				return (FAILURE);
		}
		else if (token->type == REDIR)
		{
			if (redir_err(token) == FAILURE)
				return (FAILURE);
		}
		token = token->next;
	}
	return (SUCCESS);
}










	// 	if (error == 0)
	// 	ft_putstr_fd("syntax error near unexpected token 'newline'\n",
	// 		STDERR_FILENO);
	// else if (error == 1)
	// 	ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	// else if (error == 2)
	// 	ft_putstr_fd("syntax error: unable to locate closing quotation\n",
	// 		STDERR_FILENO);
	// else if (error == 3)
	// 	ft_putstr_fd("Parser problem\n", STDERR_FILENO);
	// else if (error == 4)
	// 	ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	// else if (error == 5)
	// 	ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	// else if (error == 6)
	// 	ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	// else if (error == 7)
	// 	ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	// else if (error == 8)
	// 	ft_putendl_fd("Path does not exist", STDERR_FILENO);
	
	// 	if (token->type == PIPE_LINE)
	// 	{
	// 		if (pipe_error(token))
	// 			return (ft_perror("minishell: syntax error near"
	// 					"unexpected token `|'", NULL));
	// 	}
	// 	else if (is_redir(token->type))
	// 	{
	// 		if (redir_error(token))
	// 			return (ft_perror("minishell: syntax error near"
	// 					"unexpected token ", get_redir(token->type)));
	// 	}
	// 	else if (token->type == DOUBLE_QUOTE || token->type == QOUTE)
	// 	{
	// 		if (!check_unclosed_quotes(&token, token->type))
	// 			return (EXIT_FAILURE);
	// 	}
	// 	token = token->next;
	// }
