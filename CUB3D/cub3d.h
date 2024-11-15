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


typedef struct s_data {
	void *mlx;
	void *win;
	char **texture_paths;
} t_data;

char *ft_strdup(char *s1);

void textures_checker(t_data *data, char *file);
void map_parsing(t_data *data, char *file);

int close_window(t_data *data);
int key_hook(int keycode, t_data *data);

#endif
