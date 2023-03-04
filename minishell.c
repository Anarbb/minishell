/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/04 16:55:16 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void my_printf(const char* format, ...) {
  printf("-->|");
  va_list args;
  va_start(args, format);
  vprintf(format, args); // pass the format string and argument list to vprintf
  va_end(args); // end the variable argument list
  printf("|<--\n");
  fflush(stdout);
}

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
			parsing(shell);
			run(shell);
		}
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}

