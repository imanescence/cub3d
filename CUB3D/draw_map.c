/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:09:15 by iait-ouf          #+#    #+#             */
/*   Updated: 2024/11/15 18:24:39 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;    
	
	dst = data->data_img.addr + (y * data->data_img.line_length + x * (data->data_img.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void put_big_pixel(t_data *data, int xstart, int ystart, int unsigned color)
{
	int endY;
	int endX;
	int x;
	int y;

	x = xstart;
	endX = xstart + data->map.pixel;
	endY = ystart + data->map.pixel;
	while (x < endX - 1)
	{
		y = ystart;
		while (y < endY - 1)
		{
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;	
	}
}


/*
void	draw_player(t_data *data)
{
	int x = data->player.posX - data->player.width/2;
	int y;	

	while (x < data->player.posX + data->player.width/2)
	{
		y = data->player.posY - data->player.width/2;
		while (y < data->player.posY + data->player.width/2)
		{
			my_mlx_pixel_put(&data->img, x, y, data->player.p_color);
			y++;
		}
		x++;
	}
}
*/

void draw_map2d(t_data *data)
{
	int x;
	int y;	
	

	int yo = 0;

	while (yo < data->map.max_x * data->map.max_y)
	{
		if (yo % 8 == 0 && yo != 0)
			printf("\n");
		printf("%d", data->map.map[yo]);
		yo++;
	}
	y = 0;
	while (y < data->map.max_y)
	{
		x = 0;
		while (x < data->map.max_x)
		{
			printf ("x %d et y %d rslt de juste en dessous %d|\n", x, y, data->map.map[(y * data->map.max_x) + x]);
			if (data->map.map[y * data->map.max_x + x] == 1)
				put_big_pixel(data, x * data->map.pixel, y * data->map.pixel, 0xFFFFFF);
			else
				put_big_pixel(data, x * data->map.pixel, y * data->map.pixel, 0);
			x++;
		}
		y++;
	}
}
