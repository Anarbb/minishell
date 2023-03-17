/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/17 21:02:24 by aarbaoui         ###   ########.fr       */
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
		if (ft_lexer(shell) == SUCCESS)
		{
			if (parsing(shell) == SUCCESS)
				run(shell);
		}
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
