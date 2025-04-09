/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_char_to_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:31:06 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:06:48 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	**allocate_map(int width, int height)
{
	int	**map_int;
	int	i;

	map_int = malloc(sizeof(int *) * (height + 1));
	if (!map_int)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_int[i] = malloc(sizeof(int) * width);
		if (!map_int[i])
		{
			while (--i >= 0)
				free(map_int[i]);
			return (free(map_int), NULL);
		}
		i++;
	}
	map_int[i] = NULL;
	return (map_int);
}

int	find_max(char **tab)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (tab && tab[i])
	{
		if ((int)ft_strlen(tab[i]) > max)
			max = ft_strlen(tab[i]);
		i++;
	}
	return (max);
}

int	set_player(t_data *data, char **map, int i, int j)
{
	if (data->p->pos.x != -1)
		return (err_msg(data, "already position set for player\n"));
	init_player(data->p, j, i, map[i][j]);
	map[i][j] = '0';
	return (0);
}

void	init_map_to_int(t_data *data, char ***map)
{
	data->map_line_len = find_max(*map);
	data->map_height_len = ft_tab_size(*map);
	data->map = allocate_map(data->map_line_len, ft_tab_size(*map));
}

int	map_to_int(t_data *data, char **map)
{
	int	i;
	int	j;

	init_map_to_int(data, &map);
	if (!data->map)
		return (err_msg(data, "malloc int map fails\n"));
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '2';
			else if (map[i][j] != '1' && map[i][j] != '0'
				&& set_player(data, map, i, j))
				return (free_int_tab(data->map), 1);
			data->map[i][j] = map[i][j] - '0';
		}
		while (j < data->map_line_len)
			data->map[i][j++] = 2;
	}
	if (data->p->pos.x == -1)
		return (err_msg(data, " not position set in the map\n"), 1);
	return (0);
}
