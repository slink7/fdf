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

CFLAG = -Werror -Wall -Wextra

all : libft/libft.a $(OBJ_DIR) $(NAME)

libft/ :
	git clone git@github.com:slink7/libft.git

libft/libft.a : libft/
	git submodule update --remote libft
	cd libft/ ; make

clean :
	rm -rf $(OBJ_DIR) || true

fclean : clean
	rm $(NAME) || true

re : fclean all

$(NAME) : $(OBJ)
	cc -o $(NAME) $(OBJ) -Lmlx -lmlx -lX11 -lXext -Llibft -lft -lm

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c
	cc -g3 $(CFLAGS) -o $@ -c $< -Imlx/ -Ilibft/