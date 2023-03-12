/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/12 18:19:50 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_ops(t_shell *shell)
{
	char	*cmd;

	cmd = shell->line;
	split_by_ops(shell, cmd);
}

void	split_by_ops(t_shell *shell, char *cmd)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	start = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			add_token(shell, "<<", HERDOC);
			i++;
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
		{
			add_token(shell, ">>", REDIR_APPEND);
			i++;
		}
		else if (cmd[i] == '>')
			add_token(shell, ">", REDIR_OUT);
		else if (cmd[i] == '<')
			add_token(shell, "<", REDIR_IN);
		else if (cmd[i] == '|')
			add_token(shell, "|", PIPE);
		else if (cmd[i] == '\'')
			add_token(shell, "\'", SQUOTE);
		else if (cmd[i] == '\"')
			add_token(shell, "\"", DQUOTE);
		else if (cmd[i] == '*')
			add_token(shell, "*", WC);
		else if (cmd[i] == '$')
			add_token(shell, "$", DOLLAR);
		else if (cmd[i] == ' ')
			add_token(shell, " ", SPACE_MS);
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
    t_token *prev_tkn;
    
    prev_tkn = shell->token;
	control_d(shell->line);
	if (shell->line && *shell->line)
	{
		add_history(shell->line);
		parse_ops(shell);
		if (!validate_syntax(shell->token, prev_tkn))
		{
			expander(shell, shell->token);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}
