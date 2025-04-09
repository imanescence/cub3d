/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:32:05 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 17:40:14 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	bresenham_init(t_data *data, t_int_point p0, t_int_point p1)
{
	if (p1.x > WIDTH + 512)
		p1.x = WIDTH + 512;
	if (p1.y > HEIGHT)
		p1.y = HEIGHT;
	data->algo.dl.x = abs(p1.x - p0.x);
	data->algo.dl.y = abs(p1.y - p0.y);
	if (p0.x < p1.x)
		data->algo.sl.x = 1;
	else
		data->algo.sl.x = -1;
	if (p0.y < p1.y)
		data->algo.sl.y = 1;
	else
		data->algo.sl.y = -1;
	data->algo.err = data->algo.dl.x - data->algo.dl.y;
}

void	bresenham_algo(t_data *data, t_int_point p0,
		t_int_point p1, unsigned int color)
{
	bresenham_init(data, p0, p1);
	while (1)
	{
		if (p0.x > 0 && p0.y > 0 && p0.x < WIDTH + 512 && p0.y < HEIGHT)
			my_mlx_pixel_put(data, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		data->algo.e2 = 2 * data->algo.err;
		if (data->algo.e2 > -data->algo.dl.y)
		{
			data->algo.err -= data->algo.dl.y;
			p0.x += data->algo.sl.x;
		}
		if (data->algo.e2 < data->algo.dl.x)
		{
			data->algo.err += data->algo.dl.x;
			p0.y += data->algo.sl.y;
		}
	}
}

void	bresenham_init_map(t_data *data, t_int_point p0, t_int_point p1)
{
	if (p1.x > WIDTH + 512)
		p1.x = WIDTH + 512;
	if (p1.y > HEIGHT)
		p1.y = HEIGHT;
	data->algo.dl.x = abs(p1.x - p0.x);
	data->algo.dl.y = abs(p1.y - p0.y);
	if (p0.x < p1.x)
		data->algo.sl.x = 1;
	else
		data->algo.sl.x = -1;
	if (p0.y < p1.y)
		data->algo.sl.y = 1;
	else
		data->algo.sl.y = -1;
	data->algo.err = data->algo.dl.x - data->algo.dl.y;
}

void	bresenham_algo_map(t_data *data,
		t_int_point p0, t_int_point p1, unsigned int color)
{
	bresenham_init_map(data, p0, p1);
	while (1)
	{
		if (p0.x > 0 && p0.y > 0 && p0.x < WIDTH + 512 && p0.y < HEIGHT
			&& !(p0.x > 297 && p0.x < 780 && p0.y > 59 && p0.y < 500))
			my_mlx_pixel_put(data, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		data->algo.e2 = 2 * data->algo.err;
		if (data->algo.e2 > -data->algo.dl.y)
		{
			data->algo.err -= data->algo.dl.y;
			p0.x += data->algo.sl.x;
		}
		if (data->algo.e2 < data->algo.dl.x)
		{
			data->algo.err += data->algo.dl.x;
			p0.y += data->algo.sl.y;
		}
	}
}
