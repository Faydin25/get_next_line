/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faydin <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:00:32 by faydin            #+#    #+#             */
/*   Updated: 2022/02/09 16:17:36 by faydin           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*first_line(int fd, char *buffer)
{
	char	*buff;
	int		rd_byte;

	rd_byte = 1;
	buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!find_nl_char(buffer) && rd_byte != 0)
	{
		rd_byte = read (fd, buff, BUFFER_SIZE);
		if (rd_byte == -1)
		{
			free (buffer);
			free (buff);
			return (NULL);
		}
		buff[rd_byte] = '\0';
		buffer = strjoin(buffer, buff);
	}
	free (buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = first_line(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = get_new_line(buffer);
	buffer = get_new_buffer(buffer);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int	fd = open("deneme.txt", O_RDONLY, 0777);
	char	*c;

	c = get_next_line(fd);
	printf("%s", c);
	c = get_next_line(fd);
	printf("%s", c);
	c = get_next_line(fd);
	printf("%s", c);
	return (0);
}*/
