# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 16:12:37 by taehykim          #+#    #+#              #
#    Updated: 2022/11/14 16:12:38 by taehykim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
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
