NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = src
SRC_FILES = $(wildcard $(SRC)/*.c)

OBJ = $(SRC_FILES:.c=.o)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all
	rm -rf $(OBJ)

.PHONY: all clean fclean re