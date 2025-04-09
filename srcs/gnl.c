/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:14:28 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 18:58:49 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/gnl.h"
#include "../incl/cub3d.h"

char	*read_line(int fd, char *buffer)
{
	int		bytes_read;
	char	*line;
	char	*tmpline;
	char	*tmpbuf;

	gnl_init(&bytes_read, &tmpline, &tmpbuf);
	line = ft_get_line(buffer);
	if (ft_strchr(line, '\n'))
		return (line);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		tmpline = line;
		tmpbuf = ft_get_line(buffer);
		line = ft_strnjoin(line, tmpbuf, -1);
		free(tmpbuf);
		free(tmpline);
		if (ft_strchr(line, '\n'))
			return (line);
	}
	return (gnl_return(line));
}

char	*ft_get_line(char *s1)
{
	char	*line;

	line = NULL;
	if (s1 && ft_strchr(s1, '\n'))
	{
		line = ft_strnjoin(NULL, s1, ft_strchr(s1, '\n') - s1 + 1);
		ft_strmov(s1, ft_strchr(s1, '\n') + 1);
		return (line);
	}
	if (s1 && s1[0] && !ft_strchr(s1, '\n'))
	{
		line = ft_strnjoin(s1, NULL, 0);
		ft_strmov(s1, NULL);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];

	line = NULL;
	if (fd < 0 || fd >= OPEN_MAX)
	{
		return (NULL);
	}
	line = read_line(fd, buffer[fd]);
	return (line);
}

char	*gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}
