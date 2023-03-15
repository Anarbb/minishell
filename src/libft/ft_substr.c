/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:33:03 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/03/15 22:34:13 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	sizelen;
	size_t	newlen;

	i = 0;
	if (!s)
		return (0);
	sizelen = ft_strlen(s + start);
	if (start >= ft_strlen(s) || !len)
		return (ft_strdup(""));
	if (sizelen <= len)
		newlen = sizelen;
	else
		newlen = len;
	str = malloc(sizeof(char) * (newlen + 1));
	if (!str)
		return (0);
	while (i < newlen)
	{
		*(str + i) = *(s + i + start);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
