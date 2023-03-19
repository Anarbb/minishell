/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:11:52 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/19 18:20:21 by lsabik           ###   ########.fr       */
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
		tmp[j - 1] = '\0';
		value = get_env(shell, tmp);
		free(tmp);
		if (value)
		{
			tmp = ft_strjoin(value, str + j);
			free(str);
			str = tmp;
		}
	}
	return (str);
}

int	handle_heredoc(t_shell *shell, t_exec *exec, int fd)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, sig_herdoc);
		line = readline("> ");
		if (g_sigflag == 0)
			return (g_sigflag = 1, exec->limiter = NULL, free(line), \
				signal(SIGINT, sig_handler), 1);
		if (line == NULL)
			return (close(fd), 0);
		if (shell->inside_quotes == WITHOUT_QUOTES)
			line = expand_heredoc(shell, line, 0);
		if (ft_strcmp(line, exec->limiter) == 0)
		{
			free(line);
			return (SUCCESS);
		}
		ft_putstr(line, fd);
		ft_putchar_fd('\n', fd);
	}
	return (close(fd), SUCCESS);
}
