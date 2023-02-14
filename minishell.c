/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/14 15:53:03 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef TEST_LEXER
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *line;
	// test the function parse_ops
	t_shell	*shell;
	shell = ft_calloc(1, sizeof(t_shell));
	while (1337)
	{
		line = readline(GREEN"minishell[^,^]~>"RESET);
		shell->line = line;
		shell->token = parse_ops(shell);
		printf("token->content: %s", shell->token->content);
		free(line);
	}
	return (SUCCESS);
}
# else

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line;
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	init_shell(shell, env);
	while (1337)
	{
		init_signals();
		shell->cwd = getcwd(NULL, 0);
		line = readline(GREEN"minishell[^,^]~>"RESET);
		control_d(line);
		shell->cmd = ft_split(line, ' ');
		if(ft_strcmp(shell->cmd[0], "export") == 0)
			export_cmd(shell);
		free(line);
		free(shell->cmd);
		free(shell->cwd);
	}
	clear_history();
	return (SUCCESS);
}
#endif