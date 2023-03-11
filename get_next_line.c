/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeawdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:47:04 by akeawdou          #+#    #+#             */
/*   Updated: 2023/03/08 03:51:07 by akeawdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *) malloc(sizeof (char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = ft_readfile(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_getline(buffer);
	buffer = ft_getnext(buffer);
	return (line);
}

char	*ft_readfile(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	buffer = (char *) malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		res = ft_strjoin_free(res, buffer);
		if (ft_strchr(res, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*ft_getline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc (sizeof (char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] || buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_getnext(char *buffer)
{	
	char	*next;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free (buffer);
		return (NULL);
	}
	next = (char *) malloc (sizeof (char) * (ft_strlen(buffer) - i + 1));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
		next[j++] = buffer[i++];
	next[j] = '\0';
	free(buffer);
	return (next);
}
