GCC = gcc -Wall -Wextra -Werror

NAME = tile_tap

SRC = srcs/get_serial.c srcs/main.c

all: $(NAME)

$(NAME):
	$(GCC) -o $(NAME) $(SRC)

fclean:
	rm -f $(NAME)

re: fclean all
