NAME = philo
CC = gcc
# CFLAGS = -c 
CFLAGS = -fsanitize=thread -c # -Wall -Wextra -Werror -c
RM = rm -f
AR = ar
CRS = crs
INC_DIR = includes
SRCS_DIR = srcs

SRCS = $(addprefix $(SRCS_DIR)/, \
		main.c \
		utils.c \
		atoi.c \
		init.c \
		time.c \
		run.c \
		)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -I $(INC_DIR) $< -o $@

$(NAME): $(OBJS)
		$(CC) -o $@ $(OBJS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: fclean all clean re