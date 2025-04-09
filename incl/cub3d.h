/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:42:48 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:53:05 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "gnl.h"

# define HEIGHT 512
# define WIDTH 512

# define NO	0
# define SO	1
# define WE	2
# define EA	3
# define F	0
# define C	1

# define ESC_PRESSED 53
# define LOOK_RIGHT 124
# define LOOK_LEFT 123
# define MOVE_RIGHT 2
# define MOVE_LEFT 0
# define MOVE_UP 13
# define MOVE_DOWN 1

# define PI 3.1415925
# define DEGREE 0.0174533

typedef struct s_int_point
{
	int	x;
	int	y;
}	t_int_point;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_algo
{
	unsigned int	color;
	t_point			dl;
	t_point			sl;
	int				err;
	int				e2;
}	t_algo;

typedef struct s_img
{
	void	*id;
	char	*img_char;
	int		*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_tex
{
	float	lineh;
	float	lineoffset;
	float	ca;
	float	of;
	int		wall_height_clip;
}	t_tex;

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	float	angle;
	float	fov;
	t_point	plane;
}	t_player;

typedef struct s_wall
{
	t_img	img;
	int		bits_per_pix;
	int		bytes_per_line;
	int		endian;
}	t_wall;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		bits_per_pix;
	int		bytes_per_line;
	int		endian;
}	t_window;

typedef struct s_d3
{
	float			fov;
	t_point			poi;
	t_point			p0;
	t_point			wall_v;
	t_point			wall_h;
	float			dist_real;
	int				mx;
	int				my;
	int				mypos;
	int				chunk;
	float			atan;
	unsigned int	color;
	float			dist_v;
	float			dist_h;
}	t_d3;

typedef struct s_data
{
	t_window	*window;
	t_player	*p;
	char		*paths[4];
	long int	back[2];
	int			dir;
	t_wall		*walls;
	int			**map;
	char		**map_char;
	int			map_line_len;
	int			map_height_len;
	int			error;
	t_d3		d3;
	t_tex		tex;
	t_algo		algo;
	t_window	*bonus;
	float		coef;
}	t_data;

//3d_check.c
void	if_vertical(t_data *data, t_d3 *d3);
void	if_horizon(t_data *data, t_d3 *d3);
void	check_horizon(t_data *data, t_d3 *d3);
void	check_vertical(t_data *data, t_d3 *d3);
void	horizon_end(t_data *data, t_d3 *d3);

//3d_utils.c
void	check_angle(float *angle);
void	draw_width_line(t_data *data, t_int_point p0,
			t_int_point p1, int width);
void	draw_fc(t_data *data, int r);
void	draw_ray(t_data *data, t_d3 *d3, float r);
void	vertical_end(t_data *data, t_d3 *d3);

//texture_utils.c
void	set_tex(t_data *data, t_point *tex, float *step);
void	draw_texture_wall(t_data *data, t_point p, t_point p1);
int		check_tex(t_data *data, int i, char **tab);
int		check_set_tex(t_data *data, char **tab, int *err, int *count);

//algo.c
void	bresenham_init(t_data *data, t_int_point p0, t_int_point p1);
void	bresenham_algo(t_data *data, t_int_point p0,
			t_int_point p1, unsigned int color);
void	bresenham_init_map(t_data *data, t_int_point p0, t_int_point p1);
void	bresenham_algo_map(t_data *data, t_int_point p0,
			t_int_point p1, unsigned int color);

//check_map.c
int		check_char(char *line);
int		add_line_tab(char ***tab, char *line);
int		set_map(t_data *data, char *line, char ***map, int fd);
int		valid_map(t_data *data, char **map);
int		check_map(t_data *data, int fd);

//draw_2d.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	put_big_pixel(t_data *data, int xstart, int ystart, int unsigned color);
int		ft_int_strlen(int **tab);
void	draw_player(t_data *data, t_player *player);
void	draw_map2d(t_data *data);
void	draw_image(t_data *data);

// draw_3d.c
void	check_dist_real_v(t_data *data, t_d3 *d3);
void	check_dist_real_h(t_data *data, t_d3 *d3);
void	get_dist(t_data *data, t_d3 *d3);
void	draw_3d(t_data *data, t_d3 *d3);

//free.c
void	free_int_tab(int **tab);
void	free_char_tab(char **tab);
int		free_init(t_data *data);
int		free_path(t_data *data, int i);

//ft_split.c
char	**ft_split(char const *s, char c);

//hook.c
void	move_side(int keycode, t_data *data);
int		close_window(t_data *data);
int		check_win(t_data *data, float x, float y);
void	if_hook(int keycode, t_data *data);
int		key_hook(int keycode, t_data *data);

//init.c
void	init_player(t_player *player, float x, float y, char c);
int		set_mlx(t_data *data, t_window *window);
int		init_mlx(t_data *data);
int		init_data(t_data *data);

//libft_utils.c
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int		ft_isdigit(int c);
int		ft_atol(const char *str);

//libft_utils2.c
char	*ft_strdup(const char *src);
void	*ft_memset(void *b, int c, size_t len);

//main.c
int		err_msg(t_data *data, char *str);
int		check_xpm(char *str);
int		load_textures(t_data *data);

//map_char_to_int.c
int		**allocate_map(int width, int height);
int		find_max(char **tab);
int		set_player(t_data *data, char **map, int i, int j);
void	init_map_to_int(t_data *data, char ***map);
int		map_to_int(t_data *data, char **map);

//set_data.c
int		check_file(char *file);
int		set_data(t_data *data, char *file);

//set_texture.c
int		check_color(char **tab);
int		set_path_fc(t_data *data, int i, char **tab);
int		set_path_texture(t_data *data, char **tab);
char	*space(char *line);
int		set_texture(t_data *data, int fd);

//utils.c
int		ft_tab_size(char **tab);
int		choose_texture(char *texture_name);
int		ft_is_dir(char c);
int		if_dir(char *str);
int		if_fc(char *str);

#endif
