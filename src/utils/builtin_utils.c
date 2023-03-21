/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:17:30 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/21 18:29:14 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	join_and_free(char **tmp, char **tmp2, char *str, int *i)
{
	*tmp2 = ft_substr(str, *i, 1);
	*tmp = ft_join(*tmp, *tmp2);
	free(*tmp2);
}
