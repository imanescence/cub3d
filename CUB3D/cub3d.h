#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include "mlx.h"

// --------------- WINDOW DIMENSIONS -----------
# define WIDTH 800
# define HEIGHT 800

// --------------- KEYCODES MACROS -------------
# define X_PRESSED 17
# define ESC_PRESSED 53

typedef struct s_map {
	int *map;
	int max_x;
	int max_y;
	int pixel;
} t_map;

typedef struct s_data_img {
	void *img;
	void *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data_img;

typedef struct s_data {
	void *mlx;
	void *win;
	char **texture_paths;
	t_map map;
	t_data_img data_img;
} t_data;

char *ft_strdup(char *s1);
void ft_bzero(void *s, size_t n);
void *ft_calloc(size_t count, size_t size);
void get_map(char *file, t_data *data);

void draw_map2d(t_data *data);
void put_big_pixel(t_data *data, int xstart, int ystart, int unsigned color);

void textures_checker(t_data *data, char *file);
void map_parsing(t_data *data, char *file);

int close_window(t_data *data);
int key_hook(int keycode, t_data *data);

#endif
