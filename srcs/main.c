/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:28:33 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:38:34 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	err_msg(t_data *data, char *str)
{
	(void)data;
	write(2, "Error: ", 7);
	while (str && *str)
		write(2, str++, 1);
	return (1);
}

int	check_xpm(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i >= 4 && !ft_strncmp(".xpm", &str[i - 4], 5))
		return (0);
	return (1);
}

int	load_textures(t_data *data)
{
	int	i;

	i = 0;
	(void)data;
	while (i < 4)
	{
		if (check_xpm(data->paths[i]))
			return (err_msg(data, ": not xpm file\n"));
		data->walls[i].img.id = mlx_xpm_file_to_image(data->window->mlx,
				data->paths[i], &(data->walls[i].img.width),
				&(data->walls[i].img.height));
		if (!(data->walls[i].img.id))
			return (err_msg(data, ": fail to open the file for texture\n"));
		data->walls[i].img.img_char = mlx_get_data_addr(data->walls[i].img.id,
				&(data->walls[i].bits_per_pix),
				&(data->walls[i].bytes_per_line),
				&(data->walls[i].endian));
		data->walls[i].img.img = (int *)data->walls[i].img.img_char;
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (err_msg(NULL, "bad number of arguments\n"));
	if (init_data(&data))
		return (1);
	if (set_data(&data, av[1]))
		return (free_init(&data));
	if (set_mlx(&data, data.window))
		return (free_init(&data), free_char_tab(data.map_char), 1);
	if (load_textures(&data))
		return (free_init(&data), free_char_tab(data.map_char), 1);
	draw_image(&data);
	draw_3d(&data, &data.d3);
	mlx_hook(data.window->win, 17, 0, &close_window, &data);
	mlx_hook(data.window->win, 2, 0, &key_hook, &data);
	mlx_put_image_to_window(data.window->mlx,
		data.window->win, data.window->img.id, 0, 0);
	mlx_loop(data.window->mlx);
	return (0);
}
