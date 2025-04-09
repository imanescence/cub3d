/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:15:37 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:56:57 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	vertical_end(t_data *data, t_d3 *d3)
{
	d3->wall_v.x = d3->poi.x;
	d3->wall_v.y = d3->poi.y;
	d3->dist_v = sqrtf(((data->p->pos.x - d3->wall_v.x)
				* (data->p->pos.x - d3->wall_v.x))
			+ ((data->p->pos.y - d3->wall_v.y)
				* (data->p->pos.y - d3->wall_v.y)));
	d3->chunk = data->map_line_len;
}

void	check_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	else if ((*angle) * 180 / PI > 360)
		*angle -= 2 * PI;
}

void	draw_width_line(t_data *data, t_int_point p0, t_int_point p1, int width)
{
	int			i;
	t_int_point	pp0;
	t_int_point	pp1;

	i = -width / 2;
	pp0.y = p0.y;
	pp1.y = p1.y;
	while (i < width + width / 2)
	{
		pp0.x = p0.x + i;
		pp1.x = p1.x + i;
		bresenham_algo(data, pp0, pp1, data->d3.color);
		i++;
	}
}

void	draw_fc(t_data *data, int r)
{
	t_int_point	p;
	t_int_point	p1;

	data->d3.color = data->back[1];
	if (data->tex.of <= 440)
	{
		p.x = r * 8 + 300;
		p.y = data->tex.lineoffset + 60;
		p1.x = r * 8 + 300;
		p1.y = 60;
		draw_width_line(data, p, p1, 4);
	}
	data->d3.color = data->back[0];
	if (data->tex.of <= 440)
	{
		p.x = r * 8 + 300;
		p.y = data->tex.lineoffset + data->tex.lineh + 60;
		p1.x = r * 8 + 300;
		p1.y = 500;
		draw_width_line(data, p, p1, 4);
	}
}

void	draw_ray(t_data *data, t_d3 *d3, float r)
{
	t_point	p;
	t_point	p1;

	data->tex.lineh = (8 * 440) / d3->dist_real;
	data->tex.of = data->tex.lineh;
	if (data->tex.lineh > 440)
		data->tex.lineh = 440;
	data->tex.lineoffset = 220 - data->tex.lineh / 2;
	p.x = r * 8 + 300;
	p.y = data->tex.lineoffset + 60;
	p1.x = r * 8 + 300;
	p1.y = 60 + data->tex.lineoffset + data->tex.lineh;
	draw_texture_wall(data, p, p1);
	draw_fc(data, r);
}
