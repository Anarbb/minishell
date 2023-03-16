/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:34:51 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/16 15:06:24 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_token *token)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == CMD)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
