/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:00:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/12 18:20:01 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT && gvars->herdoc == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// void	sig_handl(int signum)
// {
// 	int fd[2];

// 	(void) signum;
// 	pipe(fd);
// 	dup2(fd[0], 0);
// 	gvars->herdoc = 0;
// 	write(fd[0], "\n", 1);
// }

void	control_d(char *line)
{
	if (!line)
	{
		ft_putstr_fd(CLEAR_LINE, 1);
		ft_putstr_fd(GREEN "minishell[^,^]~>" RESET " exit\n", 1);
		exit(EXIT_SUCCESS);
	}
}
void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
