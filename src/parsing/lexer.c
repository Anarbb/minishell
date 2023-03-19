/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 17:36:05 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_echo_arg(char *echo_start, char quote, char *cmd)
{
	int		i;
	char	*echo_end;
	char	*arg;
	(void)cmd;
	echo_end = ft_strchr(echo_start + 1, quote);
	if (!echo_end)
		echo_end = ft_strchr(echo_start + 1, '\0');
	arg = ft_substr(echo_start, 0, echo_end - echo_start);
	i = 0;
	while (arg[i])
	{
		if ((arg[i] == '<' || arg[i] == '>' || arg[i] == '|' || arg[i] == ' '))
			arg[i] = '\0';
		i++;
	}
	return (arg);
}

// void	pre_parse_echo(char *cmd, t_shell *shell)
// {

// }

void	parse_ops(t_shell *shell)
{
	char	*cmd;

	cmd = shell->line;
	// pre_parse_echo(cmd, shell);
	split_by_ops(shell, cmd);
}

void	split_by_ops(t_shell *shell, char *cmd)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			add_token(shell, ft_strdup("<<"), HERDOC);
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			add_token(shell, ft_strdup(">>"), REDIR_APPEND);
			i++;
		}
		else if (cmd[i] == '>')
			add_token(shell, ft_strdup(">"), REDIR_OUT);
		else if (cmd[i] == '<')
			add_token(shell, ft_strdup("<"), REDIR_IN);
		else if (cmd[i] == '|')
			add_token(shell, ft_strdup("|"), PIPE);
		else if (cmd[i] == '\'')
			add_token(shell, ft_strdup("\'"), SQUOTE);
		else if (cmd[i] == '\"')
			add_token(shell, ft_strdup("\""), DQUOTE);
		else if (cmd[i] == '*')
			add_token(shell, ft_strdup("*"), WC);
		else if (cmd[i] == '$')
			add_token(shell, ft_strdup("$"), DOLLAR);
		else if (cmd[i] == ' ')
			add_token(shell, ft_strdup(" "), SPACE_MS);
		else if (is_cmd_c(cmd[i]))
		{
			start = i;
			len = 1;
			while (cmd[i + 1] && is_cmd_c(cmd[i + 1]))
			{
				len++;
				i++;
			}
			add_token(shell, ft_substr(cmd, start, len), CMD);
		}
		i++;
	}
}

int	ft_lexer(t_shell *shell)
{
	t_token	*prev_tkn;

	prev_tkn = shell->token;
	control_d(shell->line);
	if (shell->line && *shell->line)
	{
		add_history(shell->line);
		parse_ops(shell);
		if (!validate_syntax(shell, shell->token, prev_tkn))
		{
			expander(shell, shell->token);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}
