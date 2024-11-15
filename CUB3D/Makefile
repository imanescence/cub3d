NAME = cub3d

INCLUDE = cub3d.h get_next_line.h

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g -g3

SRCS = main.c\
	   init_hooks.c\
	   get_next_line.c\
	   get_next_line_utils.c\
	   map_parsing.c\
	   ft_strdup.c

OBJ = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -fsanitize=address -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean :
	rm  -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
