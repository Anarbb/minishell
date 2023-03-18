/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/18 16:59:30 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*limiter_path(char *limiter, t_shell *shell)
{
	char		*new_limtr;
	static int	i;

	new_limtr = (char *)malloc(sizeof(char) * (ft_strlen(limiter) + 8));
	if (!new_limtr)
		return (NULL);
	ft_strcpy(new_limtr, "/tmp/.");
	ft_strcat(new_limtr, limiter);
	ft_strcat(new_limtr, ft_itoa(i));
	i++;
	shell->limiter = ft_strdup(new_limtr);
	return (new_limtr);
}

int	checker(t_exec *tmp)
{
	if (tmp->prev == NULL)
		return (1);
	return ((tmp->type == CMD || tmp->type == DOLLAR) && tmp->prev->type != PIPE
		&& tmp->prev->type != REDIR_OUT && tmp->prev->type != REDIR_APPEND
		&& tmp->prev->type != REDIR_IN && tmp->prev->type != HERDOC
		&& tmp->type != SPACE_MS);
}

int	fd_error(int fd, char *content)
{
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", content);
		return (FAILURE);
	}
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
	if (tokens->type == REDIR_APPEND)
	{
		exec->fd_out = open(tokens->next->content,
				O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND, 0664);
		if (fd_error(exec->fd_out, tokens->next->content) == FAILURE)
			return (FAILURE);
	}
	if (tokens->type == REDIR_IN)
	{
		exec->fd_in = open(tokens->next->content, O_RDONLY);
		if (fd_error(exec->fd_in, tokens->next->content) == FAILURE)
			return (FAILURE);
	}
	else if (tokens->type == HERDOC)
	{
		exec->limiter = tokens->next->content;
		exec->file_limiter = limiter_path(exec->limiter, shell);
		exec->fd_in = open(exec->file_limiter, O_CREAT | O_RDWR, 0777);
		if (fd_error(exec->fd_in, exec->limiter) == FAILURE)
			return (FAILURE);
		handle_heredoc(shell, exec, exec->fd_in);
	}
	return (SUCCESS);
}

int	parsing(t_shell *shell)
{
	t_exec *tmp;
	t_token *tokens;
	int i;
	// ["echo", "ks", "s", "ls"]
	// ["0", "1"]
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
			tmp->args = (char **)ft_calloc(count_cmds(tokens) + 1,
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