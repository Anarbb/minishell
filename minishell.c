/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/12 17:31:32 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_printf(const char* format, ...)
{
  printf("-->|");
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("|<--\n");
  fflush(stdout);
}

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
		set_env(shell, "PWD", getcwd(NULL, 0));
		shell->line = readline(GREEN "minishell[^,^]~> " RESET);
		shell->exit_status = 0;
		if (ft_lexer(shell) == SUCCESS)
		{
			parsing(shell);
			// run(shell, shell->exec);
		}
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
