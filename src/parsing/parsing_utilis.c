/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:35:27 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/20 19:22:20 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*limiter_path(char *limiter, t_shell *shell)
{
	char		*new_limtr;
	char		*tmp;
	static int	i;

	tmp = ft_itoa(i);
	new_limtr = (char *)malloc(sizeof(char) * (ft_strlen(limiter) + 8));
	if (!new_limtr)
		return (NULL);
	ft_strcpy(new_limtr, "/tmp/.");
	ft_strcat(new_limtr, limiter);
	ft_strcat(new_limtr, tmp);
	i++;
	free(tmp);
	if (shell->limiter)
		free(shell->limiter);
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

void	cmd_token(t_exec **tmp, t_token *tokens, int *i)
{
	if (!(*tmp)->cmd)
		(*tmp)->cmd = ft_strdup(tokens->content);
	(*tmp)->args[*i] = ft_strdup(tokens->content);
	(*tmp)->type = tokens->type;
	(*tmp)->inside_quotes = tokens->inside_quotes;
	(*i)++;
}

void	pipe_token(t_exec **tmp, t_token *tokens, int *i)
{
	(*tmp)->next = exec_new(NULL, 0);
	(*tmp)->next->prev = *tmp;
	*tmp = (*tmp)->next;
	(*tmp)->args = (char **)ft_calloc(count_cmds(tokens) + 1, \
	sizeof(char *));
	*i = 0;
}
