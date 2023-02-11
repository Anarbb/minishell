/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbaoui <aarbaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:39:20 by aarbaoui          #+#    #+#             */
/*   Updated: 2023/02/11 15:08:21 by aarbaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s1, size_t n)
{
    char *s2;
    size_t i;

    i = 0;
    s2 = (char *)malloc(sizeof(char) * (n + 1));
    if (s2 == NULL)
        return (NULL);
    while (i < n && s1[i])
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
    return (s2);
}
