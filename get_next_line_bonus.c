/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarikupu <iarikupu@s42abudhabi.ae>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:29:54 by iarikupu          #+#    #+#             */
/*   Updated: 2021/10/15 11:15:07 by iarikupu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*full_line(int fd, char *left)
{
	char	*buf;
	int		rsize;

	buf = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (! buf)
		return (NULL);
	rsize = 1;
	while (! ft_strchr(left, '\n') && rsize != 0)
	{
		rsize = read(fd, buf, BUFFER_SIZE);
		if (rsize == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rsize] = '\0';
		left = ft_strjoin(left, buf);
	}
	free(buf);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*left[2048];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	left[fd] = full_line(fd, left[fd]);
	if (! left[fd])
		return (NULL);
	line = actual_line(left[fd]);
	left[fd] = remain_line(left[fd]);
	return (line);
}
