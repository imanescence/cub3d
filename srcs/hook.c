/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:16:07 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:01:40 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	close_window(t_data *data)
{
	if (!data->window->mlx || !data->window->img.id)
		return (1);
	mlx_destroy_image(data->window->mlx, data->window->img.id);
	if (!data->window->win)
		return (1);
	mlx_destroy_window(data->window->mlx, data->window->win);
	free(data->window->mlx);
	data->window->win = NULL;
	free_init(data);
	free_char_tab(data->map_char);
	free_int_tab(data->map);
	exit (0);
}

int	check_win(t_data *data, float x, float y)
{
	int	mx;
	int	my;

	if (x > data->map_line_len * 8 && x < 0
		&& y > data->map_height_len * 8 && y < 0)
		return (0);
	mx = (int)x >> 3;
	my = (int)y >> 3;
	if (data->map[my][mx] == 1)
		return (0);
	return (1);
}

void	move_side(int keycode, t_data *data)
{
	if (keycode == MOVE_LEFT && check_win(data, data->p->pos.x
			+ cos(PI / 2 - data->p->angle) * 5, data->p->pos.y
			- sin(PI / 2 - data->p->angle) * 5))
	{
		data->p->pos.x += cos(PI / 2 - data->p->angle);
		data->p->pos.y -= sin(PI / 2 - data->p->angle);
	}
	if (keycode == MOVE_RIGHT && check_win(data, data->p->pos.x
			- cos(PI / 2 - data->p->angle) * 5, data->p->pos.y
			+ sin(PI / 2 - data->p->angle) * 5))
	{
		data->p->pos.x -= cos(PI / 2 - data->p->angle);
		data->p->pos.y += sin(PI / 2 - data->p->angle);
	}
}

void	if_hook(int keycode, t_data *data)
{
	move_side(keycode, data);
	if (keycode == MOVE_UP && check_win(data, data->p->pos.x
			+ data->p->dir.x, data->p->pos.y + data->p->dir.y))
	{
		data->p->pos.x += data->p->dir.x;
		data->p->pos.y += data->p->dir.y;
	}
	if (keycode == MOVE_DOWN && check_win(data,
			data->p->pos.x - data->p->dir.x, data->p->pos.y - data->p->dir.y))
	{
		data->p->pos.x -= data->p->dir.x;
		data->p->pos.y -= data->p->dir.y;
	}
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_PRESSED)
		close_window(data);
	if (keycode == LOOK_LEFT)
	{
		data->p->angle -= 0.1;
		if (data->p->angle < 0)
			data->p->angle += 2 * PI;
		data->p->dir.x = cos(data->p->angle);
		data->p->dir.y = sin(data->p->angle);
	}
	if (keycode == LOOK_RIGHT)
	{
		data->p->angle += 0.1;
		if (data->p->angle * 180 / PI > 360)
			data->p->angle -= 2 * PI;
		data->p->dir.x = cos(data->p->angle);
		data->p->dir.y = sin(data->p->angle);
	}
	if_hook(keycode, data);
	draw_image(data);
	draw_3d(data, &data->d3);
	mlx_put_image_to_window(data->window->mlx,
		data->window->win, data->window->img.id, 0, 0);
	return (0);
}
