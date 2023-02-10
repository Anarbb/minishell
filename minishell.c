/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/10 19:34:58 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *line;
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	while (1)
	{
		shell->env = env;
		printf(GREEN "minishell[" CYAN "%s" GREEN "]~>" RESET, getcwd(NULL, 0));
		line = readline(" ");
		if (!line)
			break ;
		init_shell(shell, env);
		shell->cmd = ft_split(line, ' ');
		if (ft_strcmp(shell->cmd[0], "cd") == 0)
			ms_cd(shell, NULL);
		if (ft_strlen(line) != 0)
			add_history(line);
		free(line);
	}
	return (0);
}