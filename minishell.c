/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/24 17:11:13 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *prompt(t_shell *shell)
{
    char *pwd;
    char *prompt;
    char *temp;

    pwd = getcwd(NULL, 0);
    if (ft_strcmp(pwd, get_env(shell, "HOME")) == 0)
    {
        free(pwd);
        pwd = ft_strdup("~");
    }
    prompt = GREEN "minishell[" BLUE;
    temp = ft_strjoin(prompt, pwd);
    prompt = ft_strjoin(temp, GREEN "]~> " RESET);
    free(temp);
    free(pwd);
    return (prompt);
}

g_sigflag = 0;

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	char *prompt_str;

	(void)ac;
	(void)av;
	prompt_str = NULL;
	shell = ft_calloc(1, sizeof(t_shell));
	init_shell(shell, env);
	while (1337)
	{
		prompt_str = prompt(shell);
		init_signals();
		shell->line = readline(prompt_str);
		free(prompt_str);
		find_path(shell, 0, 0);
		if (ft_lexer(shell) == SUCCESS)
		{
			if (parsing(shell, 0) == SUCCESS)
				run(shell, 0, NULL);
		}
		free_all(shell);
	}
	clear_history();
	return (SUCCESS);
}
