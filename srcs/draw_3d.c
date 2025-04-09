/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:10:18 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 18:46:54 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	check_dist_real_v(t_data *data, t_d3 *d3)
{
	if (d3->dist_v < d3->dist_h)
	{
		d3->poi.x = d3->wall_v.x;
		d3->poi.y = d3->wall_v.y;
		d3->dist_real = d3->dist_v;
		d3->color = 0x600000;
		if (data->p->pos.x < d3->poi.x)
		{
			data->dir = EA;
			data->coef = (d3->poi.y - (((int)d3->poi.y >> 3) << 3)) / 8;
		}
		else
		{
			data->dir = WE;
			data->coef = (((((int)d3->poi.y >> 3) << 3) + 8) - d3->poi.y) / 8;
		}
	}
}

void	check_dist_real_h(t_data *data, t_d3 *d3)
{
	if (d3->dist_v > d3->dist_h)
	{
		d3->poi.x = d3->wall_h.x;
		d3->poi.y = d3->wall_h.y;
		d3->dist_real = d3->dist_h;
		d3->color = 0xbd0000;
		if (data->p->pos.y < d3->poi.y)
		{
			data->dir = NO;
			data->coef = (d3->poi.x - (((int)d3->poi.x >> 3) << 3)) / 8;
		}
		else
		{
			data->dir = SO;
			data->coef = (((((int)d3->poi.x >> 3) << 3) + 8) - d3->poi.x) / 8;
		}
	}
}

void	get_dist(t_data *data, t_d3 *d3)
{
	t_int_point	p;
	t_int_point	p1;

	check_vertical(data, d3);
	check_horizon(data, d3);
	check_dist_real_v(data, d3);
	check_dist_real_h(data, d3);
	p.x = (int)data->p->pos.x;
	p.y = (int)data->p->pos.y;
	p1.x = (int)d3->poi.x;
	p1.y = (int)d3->poi.y;
	bresenham_algo_map(data, p, p1, 0xFF0000);
	data->tex.ca = data->p->angle - d3->fov;
	check_angle(&data->tex.ca);
	d3->dist_real *= cos(data->tex.ca);
}

void	draw_3d(t_data *data, t_d3 *d3)
{
	float	r;

	d3->fov = data->p->angle - 30 * DEGREE;
	check_angle(&d3->fov);
	r = 0;
	while (r < 60)
	{
		get_dist(data, d3);
		draw_ray(data, d3, r);
		r += 0.03125;
		d3->fov += DEGREE / 32;
		check_angle(&d3->fov);
	}
}
