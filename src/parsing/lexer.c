/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/14 17:01:10 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_ops(t_shell *shell)
{
	int	i;
	int type;

	i = 0;
	while (shell->cmd && shell->cmd[i])
	{
		if (ft_strcmp(shell->cmd[i], "|") == 0)
			type = PIPE;
		else if (ft_strcmp(shell->cmd[i], "&") == 0)
			type = AND;
		else if (ft_strcmp(shell->cmd[i], "$") == 0)
			type = DOLLAR;
		else if (ft_strcmp(shell->cmd[i], "\'") == 0
				|| ft_strcmp(shell->cmd[i], "\"") == 0)
			type = QUOTE;
		else if (ft_strcmp(shell->cmd[i], ">") == 0
				|| ft_strcmp(shell->cmd[i], "<") == 0)
			type = REDIR;
		else
			type = CMD;
		if (!shell->token)
			shell->token = token_new(ft_strdup(shell->cmd[i]), type);
		else
			token_add_back(shell->token, token_new(ft_strdup(shell->cmd[i]), type));
		i++;
		free(shell->cmd[i - 1]);
	}
}

void	ft_lexer(t_shell *shell)
{
	control_d(shell->line);
	shell->cmd = ft_split(shell->line, ' ');
	parse_ops(shell);
}