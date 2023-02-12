/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/11 20:30:30 by lsabik           ###   ########.fr       */
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
	while (1337)
	{
		shell->cwd = getcwd(NULL, 0);
		printf(GREEN "minishell[" CYAN "%s" GREEN "]~>" RESET, shell->cwd);
		line = readline(" ");
		if (!line)
			break ;
		if (!*line)
			continue;
		shell->cmd = ft_split(line, ' ');
		if(ft_strcmp(shell->cmd[0], "echo") == 0)
			echo_cmd(shell);
		if(ft_strcmp(shell->cmd[0], "cd") == 0)
			ft_cd(shell);
		if(ft_strcmp(shell->cmd[0], "export") == 0)
			export_cmd(shell);
		free(line);
		free(shell->cmd);
		free(shell->cwd);
	}
	return (0);
}
