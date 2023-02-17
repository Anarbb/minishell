/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/17 13:24:42 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_ops(t_shell *shell, char *operators)
{
	int i;
	int j;
	int type;

	i = -1;
	while (shell->cmd && shell->cmd[++i])
	{
		type = CMD;
		j = -1;
		if (is_cmd(shell->cmd[i]))
			type = CMD;
		else if (j == -1)
		{
			split_by_ops(shell, shell->cmd[i], operators);
			continue ;
		}
		if (!shell->token)
			shell->token = token_new(ft_strdup(shell->cmd[i]), type);
		else
			token_add_b(shell->token, token_new(ft_strdup(shell->cmd[i]), type));
	}
}

void split_by_ops(t_shell *shell, char *cmd, char *ops)
{
    int i = 0;
	
    while (cmd[i])
    {
        if (ft_strchr(ops, cmd[i]))
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
			else if (cmd[i] == '$')
				add_token(shell, "$", DOLLAR);
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
		parse_ops(shell, "| < << >> > \" \' *");
		if (validate_syntax(shell->token))
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}
