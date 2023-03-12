/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:49:02 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/12 15:28:48 by aarbaoui         ###   ########.fr       */
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
	int		fd_in;
	int		fd_out;
	t_token	*tokens;
	t_token	*prev;

	prev = NULL;
	tokens = shell->token;
	fd_in = 0;
	fd_out = 1;
	while (tokens)
	{
		if (tokens->type == REDIR_OUT)
		{
			fd_out = open(tokens->next->content,
							O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC,
							0664);
		}
		if (tokens->type == REDIR_APPEND)
			fd_out = open(tokens->next->content,
							O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND,
							0664);
		if (tokens->type == REDIR_IN)
			fd_in = open(tokens->next->content, O_RDONLY);
		if (tokens->type == HERDOC)
			return ;
		prev = tokens;
		tokens = tokens->next;
	}
	shell->exec->fd_in = fd_in;
	shell->exec->fd_out = fd_out;
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
	my_printf("%d:%d", tmp->fd_in, tmp->fd_out);
	while (tokens)
	{
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
		tokens = tokens->next;
	}
	tmp->args[i] = NULL;
	shell->exec = tmp;
}

// void	parsing(t_shell *shell)
// {
// 	t_exec	*tmp;
// 	char	**args;
// 	int		fd_in;
// 	int		fd_out;

// 	fd_in = 0;
// 	fd_out = 1;
// 	tmp = shell->exec;
// 	args = (char **)ft_calloc(exec_size(tmp) + 1, sizeof(char *));
// 	shell->exec->args = args;
// 	while (tmp)
// 	{
// 		if ((tmp && tmp->cmd) && checker(tmp))
// 		{
// 				*args = ft_strdup(tmp->cmd);
// 				args++;
// 				if (tmp)
// 					*args = NULL;

// 		}
// 		if (tmp->type == REDIR_OUT)
// 			fd_out = open(tmp->next->cmd,
// 					O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC, 0664);
// 		if (tmp->type == REDIR_APPEND)
// 			fd_out = open(tmp->next->cmd,
// 					O_RDWR | O_CREAT | O_CLOEXEC | O_APPEND, 0664);
// 		else if (tmp->type == REDIR_IN)
// 		{
// 			fd_in = open(tmp->next->cmd, O_RDONLY | O_CLOEXEC);
// 			if (fd_in == -1)
// 				printf("minishell: %s: No such file or directory\n",
// 						tmp->next->cmd);
// 		}
// 		else if (tmp->type == HERDOC)
// 		{
// int fd;
// signal(SIGINT, NULL);
// fd = open(limiter_path(tmp->next->cmd), O_CREAT | O_RDWR, 0777);
// if (fd == -1)
// 	printf("minishell: error: heredoc\n");
// tmp->herdoc = 1;
// shell->exec->limiter = ft_strdup(tmp->next->cmd);
// handle_heredoc(shell, shell->exec, fd);
// 		}
// 		tmp = tmp->next;
// 	}
// 	shell->exec->fd_in = fd_in;
// 	shell->exec->fd_out = fd_out;
// 	// if (shell->exec->herdoc == 1)
// 	exec_clear(&shell->exec->next);
// }

// #include "minishell.h"

// char	*limiter_path(char *limiter)
// {
// 	char	*new_limtr;
// 	static int i;

// 	new_limtr = ft_strjoin("/tmp/.", limiter);
// 	new_limtr = ft_strjoin(new_limtr, ft_itoa(i));
// 	i++;
// 	return (new_limtr);
// }

// void	handle_redirections(t_exec **exec, t_exec *current_exec)
// {
// 	if (current_exec->type == REDIR_OUT)
// 	{
// 		close((*exec)->fd_out);
// 		(*exec)->fd_out = open(current_exec->next->cmd,
// 				O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	}
// 	else if (current_exec->type == REDIR_APPEND)
// 	{
// 		close((*exec)->fd_out);
// 		(*exec)->fd_out = open(current_exec->next->cmd,
// 				O_RDWR | O_CREAT | O_APPEND, 0644);
// 	}
// 	else if (current_exec->type == REDIR_IN)
// 	{
// 		close((*exec)->fd_in);
// 		(*exec)->fd_in = open(current_exec->next->cmd, O_RDONLY);
// 		if ((*exec)->fd_in == -1)
// 			fprintf(stderr, "minishell: %s: No such file or directory\n",
// 					current_exec->next->cmd);
// 	}
// 	else if (current_exec->type == HERDOC)
// 	{
// 		close((*exec)->fd_in);
// 		(*exec)->fd_in = open(limiter_path(current_exec->next->cmd),
// 				O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		if ((*exec)->fd_in == -1)
// 			fprintf(stderr, "minishell: error: heredoc\n");
// 		(*exec)->limiter = ft_strdup(current_exec->next->cmd);
// 		current_exec->herdoc = 1;
// 	}
// }

// void	parsing(t_shell *shell)
// {
// 	t_exec	*current_exec;
// 	char	**args;

// 	current_exec = shell->exec;
// 	while (current_exec)
// 	{
// 		if (current_exec->type == CMD)
// 		{
// 			args = (char **)ft_calloc(exec_size(current_exec) + 1,
// sizeof(char *));
// 			shell->exec->args = args;
// 			while (current_exec && current_exec->type == CMD)
// 			{
// 				*args = ft_strdup(current_exec->cmd);
// 				args++;
// 				current_exec = current_exec->next;
// 			}
// 			*args = NULL;
// 		}
// 		else
// 			handle_redirections(&shell->exec, current_exec);
// 		if (current_exec)
// 			current_exec = current_exec->next;
// 	}
// }
