/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:34:51 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/14 15:37:44 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		i++;
		token = token->next;
	}
	return (i);
}
