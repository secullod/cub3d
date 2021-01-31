/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:33:07 by secullod          #+#    #+#             */
/*   Updated: 2020/07/19 17:34:53 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	append(char **str, char **line, int fd)
{
	int		len;
	char	*swap;

	len = 0;
	if (!str[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	while (str[fd][len] && str[fd][len] != '\n')
		len++;
	if (str[fd][len] == '\n')
	{
		*line = ft_substr(str[fd], 0, len);
		swap = ft_strdup(str[fd] + len + 1);
		free(str[fd]);
		str[fd] = swap;
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
	char		*swap;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buff, 0) == -1)
		return (-1);
	while ((bytes = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buff);
		else
		{
			swap = ft_strjoin(str[fd], buff);
			free(str[fd]);
			str[fd] = swap;
		}
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (append(str, line, fd));
}
