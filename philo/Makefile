NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
FUNC_DIR = ./functions
INCLUDES = -I./includes

SRCS =	$(SRC_DIR)/philosophers.c \

FUNCS =	$(FUNC_DIR)/utils_1.c $(FUNC_DIR)/utils_2.c $(FUNC_DIR)/utils_3.c \

OBJS = $(SRCS:.c=.o)
FUNCO = $(FUNCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(FUNCO)
	$(CC) -g -pthread $(CFLAGS) $(OBJS) $(FUNCO) $(INCLUDES) -o $(NAME)

%.o: %.c ./includes/philosophers.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(FUNCO)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
