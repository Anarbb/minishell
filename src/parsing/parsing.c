/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/15 23:29:46 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*limiter_path(char *limiter)
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
	g_gvars->limiter_file = ft_strdup(new_limtr);
	return (new_limtr);
}

int	checker(t_exec *tmp)
{
	if (tmp->prev == NULL)
		return (1);
	return ((tmp->type == CMD || tmp->type == DOLLAR) && tmp->prev->type != \
		PIPE && tmp->prev->type != REDIR_OUT && tmp->prev->type != REDIR_APPEND \
		&& tmp->prev->type != REDIR_IN && tmp->prev->type != HERDOC \
		&& tmp->type != SPACE_MS);
}

void	handle_redirs(t_shell *shell, t_token *tokens)
{
	int	fd;

	while (tokens)
	{
		if (tokens->type == REDIR_OUT)
			shell->exec->fd_out = open(tokens->next->content, \
			O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC, 0664);
		if (tokens->type == REDIR_APPEND)
			shell->exec->fd_out = open(tokens->next->content, \
			O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND, 0664);
		if (tokens->type == REDIR_IN)
			shell->exec->fd_in = open(tokens->next->content, O_RDONLY);
		else if (tokens->type == HERDOC)
		{
			fd = open(limiter_path(tokens->next->content), O_CREAT | O_RDWR, \
					0777);
			if (fd == -1)
				printf("minishell: error: heredoc\n");
			shell->exec->limiter = ft_strdup(tokens->next->content);
			handle_heredoc(shell, fd);
		}
		tokens = tokens->next;
	}
}

void	parsing(t_shell *shell)
{
	t_exec	*tmp;
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = shell->token;
	tmp = (t_exec *)ft_calloc(1, sizeof(t_exec));
	tmp->fd_in = 0;
	tmp->fd_out = 1;
	shell->exec = tmp;
	tmp->args = (char **)ft_calloc(count_cmds(tokens) + 1, sizeof(char *));
	handle_redirs(shell, tokens);
	while (tokens)
	{
		if ((tokens->type == REDIR_OUT || tokens->type == REDIR_IN
				|| tokens->type == REDIR_APPEND || tokens->type == HERDOC)
			&& tokens->next->type == CMD)
			delete_one_token(&tokens);
		if (tokens->type == PIPE)
		{
			tmp->next = (t_exec *)ft_calloc(1, sizeof(t_exec));
			tmp->fd_in = 0;
			tmp->fd_out = 1;
			tmp->next->prev = tmp;
			tmp = tmp->next;
			tmp->args = (char **)ft_calloc(count_cmds(tokens) + 1,
					sizeof(char *));
			handle_redirs(shell, tokens);
			i = 0;
		}
		if (tokens->type == CMD)
		{
			if (!tmp->cmd)
				tmp->cmd = ft_strdup(tokens->content);
			tmp->args[i] = ft_strdup(tokens->content);
			tmp->type = tokens->type;
			i++;
		}
		tokens = tokens->next;
	}
}
