NAME = philo
CC = cc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror 
# -fsanitize=thread
SRC_DIR = ./src
FUNC_DIR = ./functions
INCLUDES = -I./includes

SRCS =	$(SRC_DIR)/philo.c $(SRC_DIR)/philo_parsing.c $(SRC_DIR)/philo_init.c $(SRC_DIR)/philo_threads.c \
		$(SRC_DIR)/philo_actions.c $(SRC_DIR)/philo_monitor.c $(SRC_DIR)/philo_utils.c $(SRC_DIR)/philo_structs.c \
# SRCS = $(SRC_DIR)/main.c \

FUNCS =	$(FUNC_DIR)/functions_1.c $(FUNC_DIR)/functions_2.c $(FUNC_DIR)/functions_3.c \
		$(FUNC_DIR)/functions_4.c

OBJS = $(SRCS:.c=.o)
FUNCO = $(FUNCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(FUNCO)
	$(CC) -g -pthread $(CFLAGS) $(OBJS) $(FUNCO) $(INCLUDES) -o $(NAME)

%.o: %.c ./includes/philo.h ./includes/functions.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(FUNCO)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
