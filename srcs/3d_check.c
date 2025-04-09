/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:01:46 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 18:36:51 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	if_vertical(t_data *data, t_d3 *d3)
{
	if (d3->fov * 180 / PI > 90 && d3->fov * 180 / PI < 270)
	{
		d3->poi.x = (((int)data->p->pos.x >> 3) << 3) - 0.0001;
		d3->poi.y = data->p->pos.y + (data->p->pos.x - d3->poi.x) * d3->atan;
		d3->p0.x = -8;
		d3->p0.y = -d3->p0.x * d3->atan;
	}
	else if (d3->fov * 180 / PI < 90 || d3->fov * 180 / PI > 270)
	{
		d3->poi.x = (((int)data->p->pos.x >> 3) << 3) + 8;
		d3->poi.y = data->p->pos.y + (data->p->pos.x - d3->poi.x) * d3->atan;
		d3->p0.x = 8;
		d3->p0.y = -d3->p0.x * d3->atan;
	}
	else if (d3->fov * 180 / PI == 90 || d3->fov * 180 / PI == 270)
	{
		if (d3->fov * 180 / PI == 90)
			d3->poi.y = data->map_height_len * 8;
		else
			d3->poi.y = 0;
		d3->poi.x = data->p->pos.x;
		d3->chunk = data->map_height_len;
	}
}

void	if_horizon(t_data *data, t_d3 *d3)
{
	d3->dist_h = 1000000;
	d3->wall_h.x = data->p->pos.x;
	d3->wall_h.y = data->p->pos.y;
	if (d3->fov * 180 / PI > 180)
	{
		d3->poi.y = (((int)data->p->pos.y >> 3) << 3) - 0.0001;
		d3->poi.x = data->p->pos.x + ((data->p->pos.y - d3->poi.y) * d3->atan);
		d3->p0.y = -8;
		d3->p0.x = -d3->p0.y * d3->atan;
	}
	else if (d3->fov * 180 / PI < 180)
	{
		d3->poi.y = (((int)data->p->pos.y >> 3) << 3) + 8;
		d3->poi.x = data->p->pos.x + ((data->p->pos.y - d3->poi.y) * d3->atan);
		d3->p0.y = 8;
		d3->p0.x = -d3->p0.y * d3->atan;
	}
	else if (d3->fov == 0 || d3->fov * 180 / PI == 180)
	{
		d3->poi.y = data->p->pos.y;
		d3->poi.x = data->map_line_len * 8;
		d3->chunk = data->map_height_len;
	}
}

void	horizon_end(t_data *data, t_d3 *d3)
{
	d3->wall_h.x = d3->poi.x;
	d3->wall_h.y = d3->poi.y;
	d3->dist_h = sqrtf(((data->p->pos.x - d3->wall_h.x)
				* (data->p->pos.x - d3->wall_h.x))
			+ ((data->p->pos.y - d3->wall_h.y)
				* (data->p->pos.y - d3->wall_h.y)));
	d3->chunk = data->map_height_len;
}

void	check_horizon(t_data *data, t_d3 *d3)
{
	d3->chunk = 0;
	d3->atan = -1 / tan(d3->fov);
	if_horizon(data, d3);
	while (d3->chunk < data->map_height_len && (d3->poi.x
			< data->map_line_len * 8 && d3->poi.x > 0 && d3->poi.y
			< data->map_height_len * 8 && d3->poi.y > 0))
	{
		d3->mx = (int)d3->poi.x >> 3;
		d3->my = (int)d3->poi.y >> 3;
		d3->mypos = (d3->my * data->map_line_len) + d3->mx;
		if (d3->mypos >= 0 && d3->mypos < data->map_line_len
			* data->map_height_len && data->map[d3->my][d3->mx] == 1)
			horizon_end(data, d3);
		else
		{
			d3->poi.x += d3->p0.x;
			d3->poi.y += d3->p0.y;
			d3->chunk++;
		}
	}
}

void	check_vertical(t_data *data, t_d3 *d3)
{
	d3->chunk = 0;
	d3->atan = -tan(d3->fov);
	d3->dist_v = 1000000;
	d3->wall_v.x = data->p->pos.x;
	d3->wall_v.y = data->p->pos.y;
	if_vertical(data, d3);
	while (d3->chunk < data->map_line_len && (d3->poi.x < data->map_line_len * 8
			&& d3->poi.x > 0 && d3->poi.y
			< data->map_height_len * 8 && d3->poi.y > 0))
	{
		d3->mx = (int)d3->poi.x >> 3;
		d3->my = (int)d3->poi.y >> 3;
		d3->mypos = (d3->my * data->map_line_len) + d3->mx;
		if (d3->mypos >= 0 && d3->mypos
			< data->map_line_len * data->map_height_len
			&& data->map[d3->my][d3->mx] == 1)
			vertical_end(data, d3);
		else
		{
			d3->poi.x += d3->p0.x;
			d3->poi.y += d3->p0.y;
			d3->chunk++;
		}
	}
}
