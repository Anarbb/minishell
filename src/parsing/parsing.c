/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/20 20:48:51 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_parser(t_token *tokens, t_shell *shell, t_exec *exec)
{
	exec->limiter = ft_strdup(tokens->next->content);
	exec->file_limiter = limiter_path(exec->limiter, shell);
	exec->fd_in = open(exec->file_limiter, O_CREAT | O_RDWR, 0777);
	if (fd_error(exec->fd_in, exec->limiter) == FAILURE)
		return (FAILURE);
	handle_heredoc(shell, exec, exec->fd_in);
	return (SUCCESS);
}

int	handle_redirs(t_shell *shell, t_token *tokens, t_exec *exec)
{
	if (tokens->type == REDIR_OUT)
	{
		exec->fd_out = open(tokens->next->content,
				O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC, 0664);
		if (fd_error(exec->fd_out, tokens->next->content) == FAILURE)
			return (FAILURE);
	}
	else if (tokens->type == REDIR_APPEND)
	{
		exec->fd_out = open(tokens->next->content,
				O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND, 0664);
		if (fd_error(exec->fd_out, tokens->next->content) == FAILURE)
			return (FAILURE);
	}
	else if (tokens->type == REDIR_IN)
	{
		exec->fd_in = open(tokens->next->content, O_RDONLY);
		if (fd_error(exec->fd_in, tokens->next->content) == FAILURE)
			return (FAILURE);
	}
	else if (tokens->type == HERDOC)
		return (heredoc_parser(tokens, shell, exec));
	return (SUCCESS);
}

void	init_parsing(t_shell *shell, t_exec **tmp, t_token **tokens)
{
	*tokens = shell->token;
	*tmp = exec_new(NULL, 0);
	shell->exec = *tmp;
	(*tmp)->args = (char **)ft_calloc(count_cmds(*tokens) + 1, sizeof(char *));
}

int	parsing(t_shell *shell, int i)
{
	t_exec	*tmp;
	t_token	*tokens;

	init_parsing(shell, &tmp, &tokens);
	while (tokens)
	{
		if (handle_redirs(shell, tokens, tmp))
			return (FAILURE);
		if ((tokens->type == REDIR_OUT || tokens->type == REDIR_IN
				|| tokens->type == REDIR_APPEND || tokens->type == HERDOC)
			&& tokens->next->type == CMD)
			delete_one_token(&tokens);
		if (tokens->type == PIPE)
		{
			pipe_token(&tmp, tokens, &i);
			if (handle_redirs(shell, tokens, tmp))
				return (FAILURE);
		}
		if (tokens->type == CMD)
			cmd_token(&tmp, tokens, &i);
		tmp->args[i] = NULL;
		tokens = tokens->next;
	}
	return (SUCCESS);
}
