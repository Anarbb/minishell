/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:33:09 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/10 14:21:36 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

# define RESET			"\033[0m"
# define RED			"\033[1;31m"
# define GREEN			"\033[1;32m"
# define YELLOW			"\033[1;33m"
# define BLUE			"\033[1;34m"
# define CYAN 			"\033[1;36m"
# define BOLD       	"\033[1m"
# define UNDERLINE  	"\033[4m"
# define BLINK      	"\033[5m"
# define EMPTY 			1
# define WORD 			2
# define REDIRECTION	4
# define PIPE 			8
# define AND 			16
# define PARENTHESIS 	32
# define SINGLE_QUOTE 	64 
# define DOUBLE_QUOTE	128 
# define DOLAR 			255


typedef struct	s_token
{
    char			*content;
    int				type;
	struct s_token	*next;
}	t_token;

typedef struct  s_shell
{
	char	**cmd;
	int	    type;
	char	**path;
	t_token	*token;
}   t_shell;


void    init_shell(t_shell *shell, char **env);
int		find_path(t_shell *shell, char **env);

# endif