/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:33:09 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/15 17:55:44 by aarbaoui         ###   ########.fr       */
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
# define CMD 			2
# define REDIR			4
# define PIPE 			8
# define AND 			16
# define PARENTHESIS 	32
# define SINGLE_QUOTE 	64 
# define DOUBLE_QUOTE	128 
# define DOLLAR 		256
# define PARENTHESE_OPEN 512
# define PARENTHESE_CLOSE 1024
# define REDIR_OUT		2048
# define REDIR_IN		4096
# define APPEND_OUT		8192
# define APPEND_IN		16384
# define DQUOTE			32768
# define SQUOTE			65536
# define QUOTE			131072
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
void	parse_ops(t_shell *shell, char **operators);
// utils
int		is_arg(char *str);
char	*get_env(char **env, char *name);
void    add_env(t_shell *shell, char *name, char *value);
void    set_env(t_shell *shell, char *name, char *value);
t_token *token_new(char *cmd, int type);
void    token_add_b(t_token *tokens, t_token *new);
void    free_all(t_shell *shell);
// builtins
void    ft_cd(t_shell *shell);
int		echo_cmd(t_shell *shell);
int 	export_cmd(t_shell *shell);
//Signals
void	init_signals(void);
void	control_d(char	*line);
//Syntax.analyser
int 	validate_syntax(t_token *token);
//Execution
char	*find_exec(t_shell *shell, char *cmd);
#endif