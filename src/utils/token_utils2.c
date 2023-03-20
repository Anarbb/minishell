/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:29:46 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/20 18:42:06 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// if (current->content)
	// 	free(current->content);
	free(current);
	(*prev)->next = next;
}
