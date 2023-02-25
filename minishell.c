/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/25 14:28:18 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell *shell;

	shell = ft_calloc(1, sizeof(t_shell));
	init_shell(shell, env);
	while (1337)
	{
		init_signals();
		set_env(shell, "PWD", getcwd(NULL, 0));
		shell->line = readline(GREEN "minishell[^,^]~> " RESET);
		shell->exit_status = 0; 
		if (ft_lexer(shell) == SUCCESS)
		{
			char *path = find_exec(shell, shell->cmd[0]);
			exec_cmd(shell, path);
			free(path);
		}
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
