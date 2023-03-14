/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/14 14:48:40 by aarbaoui         ###   ########.fr       */
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
 
void	handle_redirs(t_shell *shell)
{
	int		fd;
	t_token	*tokens;

	tokens = shell->token;
	while (tokens)
	{
		if (tokens->type == REDIR_OUT)
		{
			shell->exec->fd_out = open(tokens->next->content,
							O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC,
							0664);
		}
		if (tokens->type == REDIR_APPEND)
			shell->exec->fd_out = open(tokens->next->content,
							O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND,
							0664);
		if (tokens->type == REDIR_IN)
			shell->exec->fd_in = open(tokens->next->content, O_RDONLY);
		else if (tokens->type == HERDOC)
		{
			signal(SIGINT, NULL);
			fd = open(limiter_path(tokens->next->content), O_CREAT | O_RDWR, 0777);
			if (fd == -1)
				printf("minishell: error: heredoc\n");
			shell->exec->limiter = ft_strdup(tokens->next->content);
			handle_heredoc(shell->exec, fd);
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
	shell->exec = tmp;
	tmp->args = (char **)ft_calloc(20, sizeof(char *));
	handle_redirs(shell);
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			tmp->next = (t_exec *)ft_calloc(1, sizeof(t_exec));
			tmp->next->prev = tmp;
			tmp = tmp->next;
			tmp->args = (char **)ft_calloc(20, sizeof(char *));
			handle_redirs(shell);
			i = 0;
		}
		if ((tokens->type == REDIR_OUT || tokens->type == REDIR_IN
				|| tokens->type == REDIR_APPEND || tokens->type == HERDOC)
			&& tokens->next->type == CMD)
			delete_one_token(&tokens);
		if (tokens->type == CMD)
		{
			if (!tmp->cmd)
				tmp->cmd = ft_strdup(tokens->content);
			tmp->args[i] = ft_strdup(tokens->content);
			tmp->type = tokens->type;
			i++;
		}
		// printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
}
// void parsing(t_shell *shell)
// {
// 	t_exec	*tmp;
// 	t_token	*tokens;
// 	int		i;

// 	i = 0;
// 	tokens = shell->token;
// 	tmp = NULL;
// 	while (tokens)
// 	{
// 		if (tokens->type == CMD)
// 		{
// 			if (!tmp)
// 			{
// 				tmp = (t_exec *)ft_calloc(1, sizeof(t_exec));
// 				shell->exec = tmp;
// 				tmp->args = (char **)malloc(sizeof(char *) * 2);
// 				// tmp->args[0] = ft_strdup(tmp->cmd);
// 				// tmp->args[1] = NULL;
// 				tmp->cmd = ft_strdup(tokens->content);
// 				tmp->type = tokens->type;
// 			}
// 			else
// 			{
// 				tmp->next = (t_exec *)ft_calloc(1, sizeof(t_exec));
// 				tmp = tmp->next;
// 				tmp->args = (char **)malloc(sizeof(char *) * 2);
// 				// tmp->args[0] = ft_strdup(tmp->cmd);
// 				// tmp->args[1] = NULL;
// 				tmp->cmd = ft_strdup(tokens->content);
// 				tmp->type = tokens->type;
// 			}
// 			i = 0;
// 		}
// 		else if (tokens->type == PIPE)
// 		{
// 			pipe = 1;
// 			i = 0;
// 		}
// 		// else if (tokens->type == CMD)
// 		// {
// 		// 	tmp->args[] = ft_strdup(tokens->content);
// 		// 	i++;
// 		// }
// 		tokens = tokens->next;
// 	}
// }
