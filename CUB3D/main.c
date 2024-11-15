#include "cub3d.h"

// parser la map elle mme avec le backtracking comme chez so long
// on trce le canva avec el max  x et max y que je trouve grace aux nb de \n 
// et en comparant les strlen de toutes les lignes et trouver la plus grande
// puis backtrack
void data_initializer(t_data *data, char *file)
{
	(void)file;
	data->map.max_x = 8;
	data->map.max_y = 8;
	data->map.pixel = 32;
	data->texture_paths = (char **) malloc (5 * sizeof (char *));
	if (!data->texture_paths)
		exit (EXIT_FAILURE);
	data->map.map = ft_calloc(data->map.max_x, data->map.max_y); 
}

void file_open_rights_verificator(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Ya un pb");
		exit (EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		perror("Closing failure");
		exit(EXIT_FAILURE);
	}
	// ICI APPELER LA FCTN BACKTRACKING
	// map_backtracker(args ?);
}

void extension_file_verificator(char *file)
{
	int i;
	int	j;
	char right_ext[5] = ".cub";
	
	i = strlen(file) - 1;
	j = strlen(right_ext) - 1;
	while (j > 0)
	{
		if (file[i] != right_ext[j])
		{
			perror("Maps must be a file with a .cub extension");
			exit (EXIT_FAILURE);
		}
		while (file[i] == right_ext[j])
		{
			i--;
			j--;
		}
	}
	file_open_rights_verificator(file);
}

void basic_parsing(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("You must provide one map to play our stylish video game !\n");
		exit (EXIT_FAILURE);
	}
	if (argc > 2)
	{
		// remplacer par strerror ????????? ou ftpustr fd ?
		printf("You don't need so many arguments to play...\n");
		exit (EXIT_FAILURE);
	}
	extension_file_verificator(argv[1]);
}

int main(int argc, char **argv)
{
	t_data data;

	basic_parsing(argc, argv);
	data_initializer(&data, argv[1]);
	map_parsing(&data, argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "CUB3D");
	if ((data.data_img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT)) == NULL)
        return (printf("error fatal\n"), 1);
 	if ((data.data_img.addr = mlx_get_data_addr(data.data_img.img, &data.data_img.bits_per_pixel, &data.data_img.line_length, &data.data_img.endian)) == NULL)
        return (printf("error fatal\n"), 1);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, X_PRESSED, 0, close_window, &data);
	draw_map2d(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.data_img.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
