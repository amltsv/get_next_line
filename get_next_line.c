/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teevee <teevee@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:56:09 by teevee            #+#    #+#             */
/*   Updated: 2020/07/29 14:27:43 by teevee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnlhelp(char **str, char **line, int fd)
{
	int		length;
	char	*tmp;

	length = 0;
	if (!str[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	while (str[fd][length] && str[fd][length] != '\n')
		length++;
	if (str[fd][length] == '\n')
	{
		*line = ft_substr(str[fd], 0, length);
		tmp = ft_strdup(str[fd] + length + 1);
		free(str[fd]);
		str[fd] = tmp;
		return (1);
	}
	else
		*line = ft_strdup(str[fd]);
	free(str[fd]);
	str[fd] = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	size_t		bytes;
	char		buff[BUFFER_SIZE + 1];
	static char *str[4096];
	char		*tmp;

	if ((fd < 0) || (!line) || (BUFFER_SIZE < 1) || (read(fd, buff, 0) == -1))
		return (-1);
	while ((bytes = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(str[fd], buff);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (gnlhelp(str, line, fd));
}
