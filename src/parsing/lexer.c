/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/16 20:21:10 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_ops(t_shell *shell, char **operators)
{
	int i;
	int j;
	int type;
	int *types;

	types = (int[9]){PIPE, REDIR_OUT, APPEND_OUT,
					 REDIR_IN, APPEND_IN, DOLLAR, SQUOTE, DQUOTE, 0};
	i = -1;
	while (shell->cmd && shell->cmd[++i])
	{
		type = CMD;
		j = -1;
		while (operators[++j])
		{
			if (ft_strcmp(shell->cmd[i], operators[j]) == 0)
			{
				type = types[j];
				break;
			}
		}
		if (!shell->token)
			shell->token = token_new(ft_strdup(shell->cmd[i]), type);
		else
			token_add_b(shell->token, token_new(ft_strdup(shell->cmd[i]), type));
	}
}

int ft_lexer(t_shell *shell)
{
	char **operators;

	operators = ft_split("| < << >> > \" \'", ' ');
	control_d(shell->line);
	if (shell->line && *shell->line)
	{
		add_history(shell->line);
		shell->cmd = ft_split(shell->line, ' ');
		parse_ops(shell, operators);
		if (validate_syntax(shell->token))
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}