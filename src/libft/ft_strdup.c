/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:32:57 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/25 15:37:52 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*res;

	if (!s1)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!(str))
		return (0);
	res = str;
	while (*s1)
	{
		*str = *s1;
		s1++;
		str++;
	}
	*str = '\0';
	return (res);
}