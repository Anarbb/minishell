/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 16:29:57 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_parser(t_token *tokens, t_shell *shell, t_exec *exec)
{
	exec->limiter = tokens->next->content;
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

int	parsing(t_shell *shell)
{
	t_exec	*tmp;
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = shell->token;
	tmp = exec_new(NULL, 0);
	shell->exec = tmp;
	tmp->args = (char **)ft_calloc(count_cmds(tokens) + 1, sizeof(char *));
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
			tmp->next = exec_new(NULL, 0);
			tmp->next->prev = tmp;
			tmp = tmp->next;
			tmp->args = (char **)ft_calloc(count_cmds(tokens) + 1, \
			sizeof(char *));
			if (handle_redirs(shell, tokens, tmp))
				return (FAILURE);
			i = 0;
		}
		if (tokens->type == CMD)
		{
			if (!tmp->cmd)
				tmp->cmd = ft_strdup(tokens->content);
			tmp->args[i] = ft_strdup(tokens->content);
			tmp->type = tokens->type;
			tmp->inside_quotes = tokens->inside_quotes;
			i++;
		}
		tmp->args[i] = NULL;
		tokens = tokens->next;
	}
	return (SUCCESS);
}
