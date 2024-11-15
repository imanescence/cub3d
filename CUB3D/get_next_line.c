/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:34:44 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:36 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *buffer)
{
	int		bytes_read;
	char	*line;
	char	*tmpline;
	char	*tmpbuf;

	tmpline = NULL;
	tmpbuf = NULL;
	bytes_read = 1;
	line = ft_get_line(buffer);
	if (ft_strchr(line, '\n'))
		return (line);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(line);
			return(NULL);
		}
		buffer[bytes_read] = '\0';
		tmpline = line;
		tmpbuf = ft_get_line(buffer);
		line = ft_strnjoin(line, tmpbuf, -1);
		free(tmpbuf);
		free(tmpline);
		if (ft_strchr(line, '\n'))
			return (line);
	}
	return (line);
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

/*#include <stdio.h>
#include"get_next_line.h"

int main() {
    int fd = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	char *line;
    //if (fd == -1)
	//{
      //  perror("Erreur lors de l'ouverture du fichier");
        //return 1;
   // }
	do
	{
		line = get_next_line(fd);
		printf("line apres return: |%s|\n", line);
	} while (line);
		line = get_next_line(fd);
		printf("ligne :");
		printf("%s\n", line);
	close(fd);
    return 0;
}*/
