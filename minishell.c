/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/20 16:45:27 by aarbaoui         ###   ########.fr       */
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
		shell->cwd = getcwd(NULL, 0);
		shell->line = readline(GREEN "minishell[^,^]~> " RESET);
		if (ft_lexer(shell) == SUCCESS)
		{
			char *path = find_exec(shell, shell->cmd[0]);
			exec_cmd(shell, path);
			free(path);
		}
		t_token *tmp = shell->token;
		while (tmp)
		{
			printf("token: %s\n", tmp->content);
			printf("type: %d\n", tmp->type);
			tmp = tmp->next;
		}
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
