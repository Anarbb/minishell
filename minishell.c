/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 21:49:05 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = ft_calloc(1, sizeof(t_shell));
	init_shell(shell, env);
	while (1337)
	{
		init_signals();
		shell->line = readline(GREEN "minishell[^,^]~> " RESET);
		find_path(shell, 0, 0);
		if (ft_lexer(shell) == SUCCESS)
		{
			if (parsing(shell, 0) == SUCCESS)
				run(shell, 0);
		}
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
