SRC = \
	main.c\
	maps.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

NAME = fdf

CFLAG = -Werror -Wall -Wextra

all : $(OBJ_DIR) $(NAME)

clean :
	rm -rf $(OBJ_DIR) || true

fclean : clean
	rm $(NAME) || true

re : fclean all

$(NAME) : $(OBJ)
	cc -o $(NAME) $(OBJ) -Lmlx -lmlx -lX11 -lXext -Llibft -lft

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c
	cc -g3 $(CFLAGS) -o $@ -c $< -Imlx/ -Ilibft/