/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkhattab <wkhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:32:50 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:16:12 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_color(char **tab)
{
	int	i;
	int	j;

	i = 0;
	if (ft_tab_size(tab) != 3)
		return (1);
	while (tab[i])
	{
		j = 0;
		while (ft_isdigit(tab[i][j]))
			j++;
		if (tab[i][j] || ft_atol(tab[i]) > 255 || ft_atol(tab[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	set_path_fc(t_data *data, int i, char **tab)
{
	char	**color;

	i = i % 4;
	if (data->back[i])
		return (err_msg(data, "already this texture in file.cub\n"));
	color = ft_split(tab[1], ',');
	if (!color)
		return (err_msg(data, "malloc error split tab\n"));
	else if (check_color(color))
	{
		free_char_tab(color);
		return (err_msg(data,
				"wrong color or wrong number of color in file.cub\n"));
	}
	else
		data->back[i] = ft_atol(color[0]) << 16 | ft_atol(color[1]) << 8
			| ft_atol(color[2]);
	free_char_tab(color);
	return (0);
}

int	set_path_texture(t_data *data, char **tab)
{
	int	i;

	if (ft_tab_size(tab) != 2)
		return (free_char_tab(tab), err_msg(data, "not good name direction\n"));
	i = choose_texture(tab[0]);
	if (i < 0)
		return (free_char_tab(tab),
			err_msg(data, "not good direction in file.cub\n"));
	if (i < 4)
	{
		if (check_tex(data, i, tab))
			return (1);
	}
	else
	{
		if (set_path_fc(data, i, tab))
			return (free_char_tab(tab), 1);
	}
	return (0);
}

char	*space(char *line)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * (ft_strlen(line) + 2));
	if (!new_line)
		return (NULL);
	new_line[0] = line[0];
	i = 1;
	if (if_dir(line))
	{
		new_line[1] = line[1];
		new_line[2] = ' ';
		i = 2;
	}
	else
		new_line[1] = ' ';
	while (line[i])
	{
		new_line[i + 1] = line[i];
		i++;
	}
	new_line[i + 1] = '\0';
	free(line);
	return (new_line);
}

int	set_texture(t_data *data, int fd)
{
	char	*line;
	char	**tab;
	int		count;
	int		err;

	count = 0;
	err = 0;
	while (count < 6)
	{
		line = gnl(fd);
		if (!line)
			return (err_msg(data, "malloc error gnl\n"));
		if ((if_dir(line) && line[2] != ' ') || (if_fc(line) && line[1] != ' '))
		{
			line = space(line);
			if (!line)
				return (free(line), err_msg(data, "malloc error new_line\n"));
		}
		tab = ft_split(line, ' ');
		if (check_set_tex(data, tab, &err, &count))
			return (free(line), 1);
		free(line);
		free_char_tab(tab);
	}
	return (err);
}
