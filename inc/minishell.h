/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:33:09 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/02 18:59:00 by lsabik           ###   ########.fr       */
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
# define REDIR_APPEND	512
# define HERDOC			1024
# define ARG			2048
# define SUCCESS		0
# define FAILURE		1

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
	struct s_env *next;
}	t_env;

typedef struct s_exec
{
	//cmd: ls -all ..
	char	*bin; // ls
	char	**args; // "ls". "-all". ".."
	int 	type; // ls //cmd //arg | >> << ls w2odq
	int		fd_in; // 0
	int		fd_out; // 1
	struct s_exec *next;
	struct s_exec *prev;
}	t_exec;

typedef struct  s_shell
{
	char	**cmd;
	t_exec	*exec;
	int	    type;
	int		exit_status;
	char	**path;
	char	*line;
	char	*cwd;
	t_env	*env;
	char	**tmp_env;
	t_token	*token;
}   t_shell;

// parsing.init
void    init_shell(t_shell *shell, char **env);
int 	find_path(t_shell *shell);
// parsing.lexer
int		ft_lexer(t_shell *shell);
void 	split_by_ops(t_shell *shell, char *cmd);
void	parse_ops(t_shell *shell);
void	add_token(t_shell *shell, char *str, int type);
int		is_cmd(char *cmd);
// utils
int		is_arg(char *str);
t_token *token_new(char *cmd, int type);
void    token_add_b(t_token *tokens, t_token *new);
void    free_all(t_shell *shell);
void	free_tokens(t_token **tokens);
int		is_cmd_c(char c);
// builtins
void    ft_cd(t_shell *shell);
int		echo_cmd(t_shell *shell);
void	ft_export(t_shell *shell, char *key, char *value);
int		exit_cmd(t_shell *shell, char *code);
void	ft_env(t_shell *shell);
void    ft_unset(t_shell *shell, char *var);
//Signals
void	init_signals(void);
void	control_d(char	*line);
//Syntax.analyser
int 	validate_syntax(t_token *token);
int		is_redirection(int type);
//Execution
char	*find_exec(t_shell *shell, char *cmd);
void	exec_cmd(t_shell *shell, char *path);
void	parsing(t_shell *shell);
//Execution.utils
t_exec	*exec_new(char *tmp, int type);
void	exec_add_b(t_shell *shell, char *tmp, int type);
void	exec_create(t_shell *shell, char *tmp, int type);
int		exec_size(t_exec *exec);
void	exec_clear(t_exec **exec);
//Expander
char	*expander(t_shell *shell, t_token *token);
char	*ft_join(char *tmp, char *value);
char	*after_dollar(t_shell *shell, char *str, char *tmp, int i);
// env
void    init_env(t_shell *shell);
void    add_env(t_shell *shell, char *key, char *value);
void    set_env(t_shell *shell, char *key, char *value);
char    *get_env(t_shell *shell, char *key);
void 	ft_lstadd_back_env(t_env **alst, t_env *new);

// debug
void my_printf(const char* format, ...);
#endif