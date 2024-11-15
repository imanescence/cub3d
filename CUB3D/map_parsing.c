/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:00:06 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/11/14 16:15:30 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

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
	int l = 0;
	while (data->texture_paths[l])
	{
		printf("%s\n|", data->texture_paths[l]);
		l++;
	}
}

void map_parsing(t_data *data, char *file)
{
	textures_checker(data, file);
}
