/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:34:51 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/19 15:26:12 by lsabik           ###   ########.fr       */
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

int	get_file_path(struct dirent **dp, DIR **dirp)
{
	*dp = readdir(*dirp);
	if (*dp == NULL)
		return (0);
	return (1);
}
