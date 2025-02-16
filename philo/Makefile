NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src
FUNC_DIR = ./functions
INCLUDES = -I./includes

SRCS =	$(SRC_DIR)/philosophers.c \

FUNCS =	$(FUNC_DIR)/functions_1.c $(FUNC_DIR)/functions_2.c $(FUNC_DIR)/functions_3.c \

OBJS = $(SRCS:.c=.o)
FUNCO = $(FUNCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(FUNCO)
	$(CC) -g -pthread $(CFLAGS) $(OBJS) $(FUNCO) $(INCLUDES) -o $(NAME)

%.o: %.c ./includes/philosophers.h ./includes/functions.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(FUNCO)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


Biti tsjli f kolchi, chofi b3da takhsossat li kat y3jbouk, w chofi fin kay tr9aw
w chofi wach kay hzo mn sience pc w wach kayn concours, wla ghir selection b no9ta
w l mdina
Mamatlobch mnk t9lbi 3la ga3 hadchi daba, ghir choufi takhsossat
Ana ghadi n chof dok li kay lo7o tssjil f Youtube wn sifthom lik, ila biti n3mr dik l Form 