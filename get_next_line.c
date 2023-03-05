/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akeawdou <akeawdou@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 15:21:23 by akeawdou          #+#    #+#             */
/*   Updated: 2023/03/05 17:34:22 by akeawdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char[FD_SETSIZE][BUFFER_SIZE]	stash;

char	*get_next_line(int fd)
{
	char	*ret;
	char	*buf;
	int		r;
	int		offset;

	buf = (char *) malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	offset = -1;
	while (offset == -1)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free (buf);
			return (NULL);
		}
		offset = ft_apndstr(ret, buf);
	}
	if (offset != 0)
		ft_rember(stash, buf, offset);
	return (ret);
}

int	ft_apndstr(char *dst, char *src)
{
	int	offset;

	if (!dst)
	{
		dst = (char *) malloc(sizeof (char));
		dst[0] = '\0';
	}
	offset = 0;
	while (src[offset] != '\n')
		offset++;

