/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:29:46 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/21 15:49:48 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_in_expander(t_shell *shell, t_token **new_tkn)
{
	t_token	*tmp_tkn;

	tmp_tkn = shell->token;
	shell->token = *new_tkn;
	free(shell->tmp);
	free_tokens(&tmp_tkn);
}

int	is_cmd_c(char c)
{
	char	**strs;
	char	**temp;

	strs = ft_split("|\n$\n<\n<<\n>>\n>\n\"\n\'\n*\n ", '\n');
	temp = strs;
	while (*strs)
	{
		if (ft_strchr(*strs, c))
		{
			free_str_arr(temp);
			return (0);
		}
		strs++;
	}
	free_str_arr(temp);
	return (1);
}

int	is_cmd(char *cmd)
{
	while (!ft_isspace(*cmd) && *cmd)
	{
		if (ft_strchr("| $ < << >> > \" \' *", *cmd))
			return (0);
		cmd++;
	}
	return (1);
}

void	delete_one_token(t_token **prev)
{
	t_token	*current;
	t_token	*next;

	current = (*prev)->next;
	next = current->next;
	free(current->content);
	free(current);
	(*prev)->next = next;
}
