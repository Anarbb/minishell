/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:11:52 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/16 15:28:10 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(t_shell *shell, char *str, int j)
{
	char	*tmp;
	char	*value;
	char	**env;

	env = shell->env_arr;
	if (str[0] == '$')
	{
		j = 1;
		if (ft_isalpha(str[j++]) || str[j++] == '_')
			while (ft_isalnum(str[j]) || str[j] == '_')
				(j)++;
		tmp = ft_strdup(str + 1);
		while (*env != NULL)
		{
			if (ft_strncmp(*env, tmp, j - 1) == 0 && (*env)[j - 1] == '=')
			{
				value = ft_strdup(*env + j);
				return (value);
			}
			env++;
		}
	}
	return (str);
}

int	handle_heredoc(t_shell *shell, t_exec *exec, int fd)
{
	char	*line;

	exec->fd_in = fd;
	while (1)
	{
		signal(SIGINT, sig_handl);
		line = readline("> ");
		if (g_gvars->herdoc == 0)
			return (g_gvars->herdoc = 1, free(line), \
				signal(SIGINT, sig_handler),
				1);
		if (line == NULL)
			return (close(fd), 0);
		if (g_gvars->inside_quotes == WITHOUT_QUOTES)
			line = expand_heredoc(shell, line, 0);
		if (ft_strcmp(line, exec->limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
	return (1);
}
