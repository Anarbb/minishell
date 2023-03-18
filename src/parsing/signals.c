/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:00:54 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/18 20:07:18 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT && g_sigflag == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_herdoc(int signum)
{
	(void)signum;
	g_sigflag = 0;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handl(int signum)
{
	g_sigflag = 0;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}

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

