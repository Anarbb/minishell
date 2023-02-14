/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:33:09 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/14 15:36:59 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define RESET			"\033[0m"
# define RED			"\033[1;31m"
# define GREEN			"\033[1;32m"
# define YELLOW			"\033[1;33m"
# define BLUE			"\033[1;34m"
# define CYAN 			"\033[1;36m"
# define BOLD       	"\033[1m"
# define UNDERLINE  	"\033[4m"
# define BLINK      	"\033[5m"
# define CLEAR_LINE		"\033[A\033[K"
# define EMPTY 			1
# define WORD 			2
# define REDIRECTION	4
# define PIPE 			8
# define AND 			16
# define PARENTHESIS 	32
# define SINGLE_QUOTE 	64 
# define DOUBLE_QUOTE	128 
# define DOLAR 			256
# define PARENTHESE_OPEN 512
# define PARENTHESE_CLOSE 1024

# define SUCCESS	0
# define FAILURE	1

typedef struct	s_token
{
    char			*content;
    int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char	*var;
	char	*value;
}	t_env;


typedef struct  s_shell
{
	char	**cmd;
	int	    type;
	char	**env;
	char	**path;
	char	*line;
	char	*cwd;
	t_env	*evn;
	t_token	*token;
}   t_shell;

// parsing.init
void    init_shell(t_shell *shell, char **env);
int		find_path(t_shell *shell, char **env);
// parsing.lexer
int		ft_lexer(t_shell *shell);
// uttils
int		is_option(char *str);
char	*get_env(char **env, char *name);
void    add_env(t_shell *shell, char *name, char *value);
void    set_env(t_shell *shell, char *name, char *value);
t_token *token_new(char *cmd, int type);
void    token_add_back(t_token *shell, t_token *new);
// builtins
void    ft_cd(t_shell *shell);
int		echo_cmd(t_shell *shell);
int 	export_cmd(t_shell *shell);
//Signals
void	init_signals(void);
void	control_d(char	*line);
#endif