/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:33:09 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/11 19:04:19 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libc.h>
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
# define EXIT_SUCCESS 	0
# define EXIT_FAILURE 	1

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
	char	**env;
	char	**path;
	char	*line;
	char	*cwd;
	t_token	*token;
}   t_shell;

// parsing.init
void    init_shell(t_shell *shell, char **env);
int		find_path(t_shell *shell, char **env);
// uttils
char	*get_env(char **env, char *name);
void    set_env(t_shell *shell, char *name, char *value);
// builtins
void    ft_cd(t_shell *shell);
void    ft_echo(char **args);
# endif