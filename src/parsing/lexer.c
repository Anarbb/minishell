/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/25 20:55:11 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_ops(t_shell *shell)
{
	char	*cmd;

	cmd = shell->line;
	split_by_ops(shell, cmd, 0, 0);
}

void	split_by_ops_2(char *cmd, int *i, t_shell *shell, int *start)
{
	int	len;

	if (cmd[*i] == '\"')
		add_token(shell, ft_strdup("\""), DQUOTE);
	else if (cmd[*i] == '*')
		add_token(shell, ft_strdup("*"), WC);
	else if (cmd[*i] == '$')
		add_token(shell, ft_strdup("$"), DOLLAR);
	else if (cmd[*i] == ' ')
		add_token(shell, ft_strdup(" "), SPACE_MS);
	else if (is_cmd_c(cmd[*i]))
	{
		*start = *i;
		len = 1;
		while (cmd[(*i) + 1] && is_cmd_c(cmd[(*i) + 1]))
		{
			len++;
			(*i)++;
		}
		add_token(shell, ft_substr(cmd, *start, len), CMD);
	}
}

void	split_by_ops(t_shell *shell, char *cmd, int i, int start)
{
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
		else
			split_by_ops_2(cmd, &i, shell, &start);
		i++;
	}
}

int	ft_lexer(t_shell *shell)
{
	t_token	*prev_tkn;

	prev_tkn = shell->token;
	control_d(shell->line, shell);
	if (shell->line && *shell->line)
	{
		add_history(shell->line);
		parse_ops(shell);
		if (!validate_syntax(shell, shell->token, prev_tkn))
		{
			expander(shell, shell->token, NULL, NULL);
			return (SUCCESS);
		}
		else
			shell->exit_status = 258;
	}
	return (FAILURE);
}
