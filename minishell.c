/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/14 21:02:35 by lsabik           ###   ########.fr       */
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
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	init_shell(shell, env);
	while (1337)
	{
		init_signals();
		shell->cwd = getcwd(NULL, 0);
		shell->line = readline(GREEN"minishell[^,^]~>"RESET);
		ft_lexer(shell);
		// while (shell->token)
		// {
		// 	printf("token->content: %s, token->type: %d\n", shell->token->content, shell->token->type);
		// 	shell->token = shell->token->next;
		// }
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
#endif