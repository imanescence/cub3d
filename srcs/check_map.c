/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:57:14 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 18:37:53 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_char(char *line)
{
	int			i;
	int			j;
	char		good_char[7];

	good_char[0] = ' ';
	good_char[1] = '0';
	good_char[2] = '1';
	good_char[3] = 'N';
	good_char[4] = 'S';
	good_char[5] = 'W';
	good_char[6] = 'E';
	i = 0;
	while (line && line[i])
	{
		j = 0;
		while (good_char[j] && line[i] != good_char[j])
			j++;
		if (!good_char[j])
			return (1);
		i++;
	}
	return (0);
}

int	add_line_tab(char ***tab, char *line)
{
	int		i;
	char	**new_tab;

	new_tab = malloc(sizeof(char *) * (ft_tab_size(*tab) + 2));
	if (!new_tab)
		return (1);
	i = 0;
	while (*tab && (*tab)[i])
	{
		new_tab[i] = (*tab)[i];
		i++;
	}
	new_tab[i++] = line;
	new_tab[i] = NULL;
	if (*tab)
		free(*tab);
	*tab = new_tab;
	return (0);
}

int	set_map(t_data *data, char *line, char ***map, int fd)
{
	while (line)
	{
		if (!(*line))
			return (err_msg(data, "line is empty\n"));
		else if (add_line_tab(map, line))
			return (free(line), err_msg(data, "malloc error\n"));
		else if (check_char(line))
			return (err_msg(data, " wrong char in map in file.cub\n"));
		line = get_next_line(fd);
		if (ft_strchr(line, '\n'))
			line[ft_strlen(line) - 1] = '\0';
	}
	return (0);
}

int	valid_map(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] && i < ft_tab_size(map))
	{
		j = -1;
		while (map[i][++j])
		{
			if ((!i || i == ft_tab_size(map) - 1 || !j
					|| j == (int)ft_strlen(map[i]) - 1)
				&& map[i][j] == '0')
				return (err_msg(data, "invalid map\n"));
			if ((map[i][j] == '0' || ft_is_dir(map[i][j]))
					&& (map[i + 1][j] == 0
					|| map[i - 1][j] == 0 || map[i][j + 1] == 0
					|| map[i][j - 1] == 0 || map[i + 1][j] == 32
					|| map[i - 1][j] == 32 || map[i][j + 1] == 32
					|| map[i][j - 1] == 32))
				return (err_msg(data, "invalid map\n"));
		}
		i++;
	}
	return (0);
}

int	check_map(t_data *data, int fd)
{
	char	**map;
	char	*line;

	line = gnl(fd);
	while (line && !(*line))
	{
		free(line);
		line = gnl(fd);
	}
	if (!line)
		return (err_msg(data, "malloc error or not map in file.cub"));
	else
	{
		map = NULL;
		if (set_map(data, line, &map, fd))
			return (free_char_tab(map), 1);
		if (valid_map(data, map))
			return (free_char_tab(map), 1);
		if (map_to_int(data, map))
			return (free_char_tab(map), 1);
		data->map_char = map;
	}
	return (0);
}
