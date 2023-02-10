/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:35:46 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/10 14:49:36 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *line;
	t_shell	*shell;
	
	shell = ft_calloc(1, sizeof(t_shell));
	while (1)
	{
		line = readline(GREEN "minishell[" RED ">.<" GREEN "]~>" RESET);
		if (!line)
			break ;
		init_shell(shell, env);
		add_history(line);
		free(line);
	}
	return (0);
}