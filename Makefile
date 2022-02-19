# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/19 19:22:34 by aabajyan          #+#    #+#              #
#    Updated: 2022/02/19 19:37:27 by aabajyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
SRCS = $(wildcard src/ft/*.c) $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
CFLAGS = -Wall -Wextra -Werror -g -O0 -I./src
LDFLAGS = $(CFLAGS) -lreadline

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean re fclean all
