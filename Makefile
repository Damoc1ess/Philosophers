CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft -g

LIBFT_TARGET = libft/libft.a

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRC_FILES:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_TARGET)
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_TARGET):
	@make -C libft

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
