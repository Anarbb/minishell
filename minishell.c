/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/15 18:31:01 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_shell *shell, char *path)
{
	pid_t	pid;
	int		status;

	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(shell->cmd[0], 2);
		return ;
	}
	if (ft_strcmp(shell->cmd[0], "exit") == 0)
		exit(0);
	if (ft_strcmp(shell->cmd[0], "cd") == 0)
		ft_cd(shell);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, &shell->cmd[0], shell->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(shell->cmd[0], 2);
			exit(0);
		}
	}
	else
		waitpid(pid, &status, 0);
}


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	init_shell(shell, env);
	while (1337)
	{
		init_signals();
		shell->cwd = getcwd(NULL, 0);
		shell->line = readline(GREEN"minishell[^,^]~> "RESET);
		if (ft_lexer(shell))
			exec_cmd(shell, find_exec(shell, shell->cmd[0]));
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
