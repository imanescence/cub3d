#include "cub3d.h"

int close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit (EXIT_SUCCESS);
}

int key_hook(int keycode, t_data *data)
{
	if (keycode == ESC_PRESSED)
		close_window(data);
	return (0);
}
