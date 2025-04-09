/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:00:37 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 17:42:38 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->window->img.img_char
		+ (y * data->window->bytes_per_line
			+ x * (data->window->bits_per_pix / 8));
	*(unsigned int *)dst = color;
}

void	put_big_pixel(t_data *data, int xstart, int ystart, int unsigned color)
{
	int	endy;
	int	endx;
	int	x;
	int	y;

	x = xstart;
	endx = xstart + 8;
	endy = ystart + 8;
	while (x < endx - 1)
	{
		y = ystart;
		while (y < endy - 1)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_player(t_data *data, t_player *player)
{
	float	x_start;
	float	y_start;

	x_start = (player->pos.x) - 2;
	while (x_start < (player->pos.x) + 2)
	{
		y_start = (player->pos.y) - 2;
		while (y_start < (player->pos.y) + 2)
		{
			my_mlx_pixel_put(data, x_start, y_start, 0xFF0000);
			y_start++;
		}
		x_start++;
	}
}

void	draw_map2d(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_tab_size(data->map_char))
	{
		j = 0;
		while (j < ft_strlen(data->map_char[i]))
		{
			if (data->map[i][j] == 1)
				put_big_pixel(data, j * 8, i * 8, 0xFFFFFF);
			else
				put_big_pixel(data, j * 8, i * 8, 0);
			j++;
		}
		i++;
	}
	draw_player(data, data->p);
}

void	draw_image(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH + 512)
	{
		y = 0;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(data, x, y, 0x808080);
			y++;
		}
		x++;
	}
	draw_map2d(data);
}
