/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:33:09 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/13 13:18:38 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define BLINK "\033[5m"
# define CLEAR_LINE "\033[A\033[K"
# define EMPTY 1
# define CMD 2
# define PIPE 4
# define REDIR_OUT 8
# define REDIR_IN 16
# define SQUOTE 32
# define DQUOTE 64
# define WC 128
# define DOLLAR 256
# define REDIR_APPEND 512
# define HERDOC 1024
# define ARG 2048
# define SPACE_MS 4096
# define SUCCESS 0
# define FAILURE 1

typedef struct s_global
{
	int				herdoc;
	int				exit_status;
}					t_global;

t_global			*gvars;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_exec
{
	//cmd: ls -all ..
	char *cmd;   // ls
	char **args; // "ls". "-all". ".."
	int type;    // ls //cmd //arg | >> << ls w2odq
	int fd_in;   // 0
	int fd_out;  // 1
	char			*limiter;
	struct s_exec	*next;
	struct s_exec	*prev;
}					t_exec;

typedef struct s_shell
{
	char			**cmd;
	char			**env_arr;
	t_exec			*exec;
	int				type;
	int				exit_status;
	char			**path;
	char			*line;
	char			*cwd;
	t_env			*env;
	char			**tmp_env;
	t_token			*token;
}					t_shell;

// parsing.init
void				init_shell(t_shell *shell, char **env);
int					find_path(t_shell *shell);
// parsing.lexer
int					ft_lexer(t_shell *shell);
void				split_by_ops(t_shell *shell, char *cmd);
void				parse_ops(t_shell *shell);
void				add_token(t_shell *shell, char *str, int type);
t_token				*create_token(t_token *token, char *cmd, int type);
int					is_cmd(char *cmd);
// utils
int					is_arg(char *str);
t_token				*token_new(char *cmd, int type);
void				token_add_b(t_token *tokens, t_token *new);
void				free_all(t_shell *shell);
void				free_tokens(t_token **tokens);
int					is_cmd_c(char c);
void				delete_one_token(t_token **token);
// builtins
void				ft_cd(t_shell *shell, t_exec *exec);
int					ft_echo(t_exec *exec);
void				ft_export(t_shell *shell, t_exec *exec);
int					ft_exit(t_shell *shell);
void				ft_env(t_shell *shell);
void				ft_unset(t_shell *shell);
//Signals
void				init_signals(void);
void				control_d(char *line);
void				sig_handl(int signum);
//Syntax.analyser
int 	validate_syntax(t_token *token, t_token *prev_tkn);
int		is_redirection(int type);
//Execution
char				*find_exec(t_shell *shell, char *cmd);
void				exec_cmd(t_shell *shell, t_exec *exec, char *path);
void				parsing(t_shell *shell);
void				pipe_handler(t_exec *exec);
void				run(t_shell *shell, t_exec *exec);
//Execution.utils
t_exec				*exec_new(char *tmp, int type);
void				exec_add_b(t_shell *shell, char *tmp, int type);
void				exec_create(t_shell *shell, char *tmp, int type);
int					exec_size(t_exec *exec);
void				exec_clear(t_exec **exec);
char				*limiter_path(char *limiter);
int					count_commands(t_exec *exec);
//Expander
void				expander(t_shell *shell, t_token *token);
char				*ft_join(char *tmp, char *value);
char				*after_dollar(t_shell *shell, char *str, char *tmp, int i);
//Expander.utils
char				*expand_after_dollar(t_shell *shell, char *str, int *i,
						int j);
void				expand_in_dquote(t_token **token, t_shell *shell,
						t_token **new_tkn);
void				expand_in_squote(t_token **token, t_token **new_tkn);
void				skip_spaces(t_token **token, t_token **new_tkn, char *tmp);
// env
void				init_env(t_shell *shell);
void				add_env(t_shell *shell, char *key, char *value);
void				set_env(t_shell *shell, char *key, char *value);
char				*get_env(t_shell *shell, char *key);
void				ft_lstadd_back_env(t_env **alst, t_env *new);
void				unset_env(t_shell *shell, char *key);
// heredoc
void	handle_heredoc(t_exec *exec, int fd);
void	sig_handler(int signum);
// debug
void				my_printf(const char *format, ...);
#endif