/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/20 12:14:02 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_ops(t_shell *shell)
{
	int i;

	i = -1;
	while (shell->cmd && shell->cmd[++i])
		split_by_ops(shell, shell->cmd[i]);
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
            add_token(shell, "<<", APPEND_IN);
            i++;
        }
        else if (cmd[i] == '>' && cmd[i + 1] == '>')
        {
            add_token(shell, ">>", APPEND_OUT);
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
        else if (is_cmd_c(cmd[i]))
        {
            start = i;
            len = 1;
            while (!ft_isspace(cmd[i + 1]) && cmd[i + 1] && is_cmd_c(cmd[i + 1]))
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
		shell->cmd = ft_split(shell->line, ' ');
		parse_ops(shell);
		if (!validate_syntax(shell->token))
		{
			expander(shell, shell->token);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}
