/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/11 17:59:51 by aarbaoui         ###   ########.fr       */
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
	init_shell(shell, env);
	while (1)
	{
		shell->cwd = getcwd(NULL, 0);
		printf(GREEN "minishell[" CYAN "%s" GREEN "]~>" RESET, shell->cwd);
		line = readline(" ");
		if (!line)
			break ;
		shell->cmd = ft_split(line, ' ');
		free(line);
		free(shell->cmd);
		free(shell->cwd);
	}
	return (0);
}