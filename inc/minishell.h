/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:33:09 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/17 15:12:20 by lsabik           ###   ########.fr       */
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
# define PIPE 			4
# define REDIR_OUT		8
# define REDIR_IN 		16
# define SQUOTE		 	32
# define DQUOTE 		64 
# define WC				128 
# define DOLLAR 		256
# define APPEND_OUT		512
# define APPEND_IN		1024
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
	int		exit_status;
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
void split_by_ops(t_shell *shell, char *cmd, char *ops);
void	parse_ops(t_shell *shell, char *operators);
void	add_token(t_shell *shell, char *str, int type);
int		is_cmd(char *cmd);
// utils
int		is_arg(char *str);
char	*get_env(char **env, char *name);
void    add_env(t_shell *shell, char *name, char *value);
void    set_env(t_shell *shell, char *name, char *value);
t_token *token_new(char *cmd, int type);
void    token_add_b(t_token *tokens, t_token *new);
void    free_all(t_shell *shell);
void	free_tokens(t_token **tokens);
// builtins
void    ft_cd(t_shell *shell);
int		echo_cmd(t_shell *shell);
int 	export_cmd(t_shell *shell);
int		exit_cmd(t_shell *shell, char *code);
//Signals
void	init_signals(void);
void	control_d(char	*line);
//Syntax.analyser
int 	validate_syntax(t_token *token);
int		is_redirection(int type);
//Execution
char	*find_exec(t_shell *shell, char *cmd);
void	exec_cmd(t_shell *shell, char *path);
//Expander
void    expand_tokens(t_shell *shell);
char	*expander(t_shell *shell, char *str);
#endif