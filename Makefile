NAME = cub3D

INCLUDE =	incl/cub3d.h	\
			incl/gnl.h			\

CFLAGS = -Wall -Werror -Wextra -I/usr/X11/include -lmlx -framework OpenGL -framework AppKit

SRCS =	srcs/main.c				\
		srcs/free.c				\
		srcs/ft_split.c			\
		srcs/gnl.c				\
		srcs/gnl_utils.c		\
		srcs/hook.c				\
		srcs/init.c				\
		srcs/libft_utils.c		\
		srcs/libft_utils2.c		\
		srcs/map_char_to_int.c	\
		srcs/set_data.c			\
		srcs/set_texture.c		\
		srcs/texture_utils.c	\
		srcs/utils.c			\
		srcs/draw_2d.c			\
		srcs/draw_3d.c			\
		srcs/3d_check.c			\
		srcs/3d_utils.c			\
		srcs/check_map.c		\
		srcs/algo.c				\

OBJ = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean :
	rm  -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
