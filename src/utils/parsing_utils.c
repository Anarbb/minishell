/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:34:51 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/16 13:55:15 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		if (token->type == SPACE)
			i++;
		token = token->next;
	}
	return (i);
}
