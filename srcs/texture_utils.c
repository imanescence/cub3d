/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:29:20 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:39:07 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	set_tex(t_data *data, t_point *tex, float *step)
{
	tex->x = data->coef * (float)(data->walls[data->dir].img.width);
	tex->y = 0;
	if (data->tex.of < 440)
		*step = (float)data->walls[data->dir].img.height / (float)data->tex.of;
	else
	{
		tex->y = ((((float)data->tex.of / 2) - ((float)440 / 2)) / data->tex.of)
			* (float)data->walls[data->dir].img.height;
		*step = (float)data->walls[data->dir].img.height / (float)data->tex.of;
	}
}

void	draw_texture_wall(t_data *data, t_point p, t_point p1)
{
	int			start;
	int			end;
	t_point		tex;
	float		step;

	start = p.y;
	end = p1.y;
	set_tex(data, &tex, &step);
	while (start < end)
	{
		data->window->img.img[(int)(start * (WIDTH + 512) + p.x - 2)]
			= data->walls[data->dir].img.img[
			data->walls[data->dir].img.width * (int)tex.y + (int)tex.x];
		tex.y += step;
		start++;
	}
}

int	check_tex(t_data *data, int i, char **tab)
{
	if (data->paths[i])
		return (free_char_tab(tab),
			err_msg(data, "already this texture in file.cub\n"));
	else
	{
		data->paths[i] = ft_strdup((tab[1]));
		if (!data->paths[i])
			return (free_path(data, i), free_char_tab(tab),
				err_msg(data, "malloc error path texture\n"));
	}
	return (0);
}

int	check_set_tex(t_data *data, char **tab, int *err, int *count)
{
	if (!tab)
		return (err_msg(data, "malloc error split tab\n"));
	if (*tab && ++(*count))
		*err = set_path_texture(data, tab);
	if (*err)
		return (*err);
	return (0);
}
