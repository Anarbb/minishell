/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsabik <lsabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 15:57:41 by lsabik            #+#    #+#             */
/*   Updated: 2023/03/05 16:04:30 by lsabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	strlast(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_line(char **static_buff)
{
	char	*tmp;
	char	*line;
	int		i;

	if (*static_buff == 0 || **static_buff == 0)
		return (0);
	i = 0;
	i = strlast(*static_buff, '\n');
	line = ft_substr(*static_buff, 0, i + 1);
	tmp = ft_strdup(&(*static_buff)[i + 1]);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = 0;
	}
	free(*static_buff);
	*static_buff = tmp;
	return (line);
}

int	read_lines(int fd, char **static_buff, int buffer_size)
{
	int		readed;
	char	*buff;

	readed = 1;
	buff = malloc(sizeof(char) * buffer_size + 1);
	if (!buff)
		return (0);
	while (strlast(*static_buff, '\n') == -1 && readed)
	{
		readed = read(fd, buff, buffer_size);
		if (readed <= 0)
		{
			free(buff);
			return (0);
		}
		buff[readed] = '\0';
		*static_buff = ft_strjoin(*static_buff, buff);
	}
	free(buff);
	return (readed);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			readed;
	static char	*static_buff[OPEN_MAX];
	char		*tmp;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	readed = read_lines(fd, &static_buff[fd], 2);
	if (!readed)
	{
		tmp = static_buff[fd];
		static_buff[fd] = 0;
		return (tmp);
	}
	if (readed == -1)
		return (NULL);
	line = extract_line(&static_buff[fd]);
	return (line);
}