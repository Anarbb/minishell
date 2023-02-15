/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/15 17:00:36 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("lexer success\n");
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
