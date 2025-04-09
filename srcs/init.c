/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:24:10 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:03:55 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	set_mlx(t_data *data, t_window *window)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (err_msg(data, "mlx init fail\n"));
	window->win = mlx_new_window(window->mlx, WIDTH + 512, HEIGHT, "CUB3D");
	if (!window->win)
		return (err_msg(data, "mlx new window fail\n"));
	window->img.id = mlx_new_image(window->mlx, WIDTH + 512, HEIGHT);
	if (!(window->img.id))
		return (err_msg(data, "mlx new image fail\n"));
	window->img.img_char = mlx_get_data_addr
		(window->img.id, &(window->bits_per_pix),
			&(window->bytes_per_line), &(window->endian));
	if (!window->img.img_char)
		return (err_msg(data, "mlx get data addr fail\n"));
	window->img.img = (int *)(window->img.img_char);
	return (0);
}

void	init_player(t_player *player, float x, float y, char c)
{
	player->pos.x = x * 8 + 0.5;
	player->pos.y = y * 8 + 0.5;
	player->dir.x = 0;
	player->dir.y = 0;
	if (c == 'N')
	{
		player->angle = 270 * PI / 180;
		player->dir.y = -1;
	}
	else if (c == 'S')
	{
		player->angle = 90 * PI / 180;
		player->dir.y = 1;
	}
	else if (c == 'W')
	{
		player->angle = PI;
		player->dir.x = -1;
	}
	else
	{
		player->angle = 0;
		player->dir.x = 1;
	}
}

int	init_mlx(t_data *data)
{
	data->back[0] = '\0';
	data->back[1] = '\0';
	data->map = NULL;
	data->error = 0;
	data->window = NULL;
	data->walls = NULL;
	data->window = malloc(sizeof(t_window));
	if (data->window == NULL)
		return (err_msg(NULL, "malloc error\n"));
	data->window->mlx = NULL;
	data->window->win = NULL;
	data->window->bytes_per_line = 4 * WIDTH;
	data->window->bits_per_pix = 8;
	data->window->endian = 1;
	return (0);
}

int	init_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		data->paths[i] = NULL;
	if (init_mlx(data))
		return (1);
	data->p = NULL;
	data->p = malloc(sizeof(t_player));
	if (!data->p)
	{
		free(data->window);
		return (err_msg(NULL, "malloc error\n"));
	}
	data->p->pos.x = -1;
	data->walls = malloc(sizeof(t_wall) * 4);
	if (!data->walls)
	{
		free(data->window);
		free(data->p);
		return (err_msg(NULL, "malloc error\n"));
	}
	return (0);
}
