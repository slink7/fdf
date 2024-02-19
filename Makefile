SRC = \
	draw_map.c\
	hooks.c\
	image.c\
	load_map.c\
	main.c\
	project.c\
	put_line.c\
	vec.c\

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

NAME = fdf

CFLAGS = -Werror -Wall -Wextra

all : $(OBJ_DIR) $(NAME)

libs:
	cd libft/ ; make
	cd mlx/ ; make

clean :
	rm -rf $(OBJ_DIR) || true

fclean : clean
	rm $(NAME) || true

re : fclean all

$(NAME) : libs $(OBJ)
	cc -o $(NAME) $(OBJ) -Lmlx -lmlx -lX11 -lXext -Llibft -lft -lm

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c
	cc -g3 $(CFLAGS) -o $@ -c $< -Imlx/ -Ilibft/