/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:00:06 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/11/15 18:24:29 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (!s)
		exit(EXIT_FAILURE);
	if (n <= 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*n;
	size_t	tmp;

	tmp = count * size;
	if (size != 0 && count != tmp / size)
		return (0);
	n = malloc(count * size);
	if (n == NULL)
		exit (EXIT_FAILURE);
	ft_bzero(n, count * size);
	return (n);
}

void	get_map(char *file, t_data *data)
{
	int fd;
	int i;
	int line;
	char *col;
	char s[2];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	col = get_next_line(fd);
	line = 0;
	while (col != NULL)
	{
		i = 0;
		while (i < data->map.max_x)
		{
			s[0] = col[i];
			s[1] = '\0';
			data->map.map[line * data->map.max_y + i] = atoi(s);
			i++;
		}
		col = get_next_line(fd);
		line++;
	}
	close (fd);
}

void textures_checker(t_data *data, char *file)
{
	int	i;
	int fd;

	i = 0;
	fd = open(file, O_RDONLY);
	while (i < 4)
	{
		data->texture_paths[i] = ft_strdup(get_next_line(fd));
		i++;
	}
	data->texture_paths[i] = NULL;
	close (fd);	
}

void map_parsing(t_data *data, char *file)
{
	textures_checker(data, file);
	get_map(file, data);
}
