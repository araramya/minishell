# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/19 19:22:34 by aabajyan          #+#    #+#              #
#    Updated: 2022/02/19 19:22:36 by aabajyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
CFLAGS = -Wall -Wextra -Werror -g -O0
LDFLAGS = $(CFLAGS) -lreadline

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean re fclean all
