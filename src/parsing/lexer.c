/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/09 16:52:01 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_ops(t_shell *shell)
{
	int i;
    char *cmd;

    cmd = shell->line;
	i = -1;
	split_by_ops(shell, cmd);
}

void split_by_ops(t_shell *shell, char *cmd)
{
    int i = 0;
    int start = 0;
    int len = 0;

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

int ft_lexer(t_shell *shell)
{
	control_d(shell->line);
	if (shell->line && *shell->line)
	{
		add_history(shell->line);
		parse_ops(shell);
		if (!validate_syntax(shell->token))
		{
			expander(shell, shell->token);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}
