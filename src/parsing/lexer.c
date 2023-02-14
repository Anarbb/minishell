/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:00:25 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/14 16:31:15 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*parse_ops(t_shell *shell)
{
	int	i;
	int type;

	i = 0;
	while (shell->line && shell->line[i])
	{
		if (shell->line[i] == '|')
			type = PIPE;
		else if (shell->line[i] == '>')
			type = REDIR_OUT;
		else if (shell->line[i] == '<')
			type = REDIR_IN;
		else
			return (shell->token);
		shell->token = token_new(ft_substr(shell->line, i, 1), type);
		shell->line = ft_substr(shell->line, i + 1, ft_strlen(shell->line));
		i = 0;
	}
	return (shell->token);
}

// void	*ft_lexer(t_shell *shell)
// {
// 	int	i;
	
// 	i = 0;
// 	shell->token = NULL;
// 	shell->cmd = ft_split(shell->line, ' ');
// 	tokens = parse_ops(shell);
// 	while (shell->cmd[i])
// 	{
// 		shell->token = token_new(shell->cmd[i], CMD);
// 		i++;
// 	}
// 	return (shell->token);
// }