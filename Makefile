# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftadeu-d <ftadeu-d@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/26 23:40:40 by ftadeu-d          #+#    #+#              #
#    Updated: 2021/09/26 23:46:47 by ftadeu-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
FLAGS = -Wall -Wextra -Werror

SRC = ./main.c\
		./split.c\
		./utils.c

OBJ = ./main.o\
		./split.o\
		./utils.o

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJ): $(SRC)
		$(CC) $(FLAGS) -c $(SRC)

clean:
		rm -f $(OBJ)

fclean:
		rm -f $(NAME)
		rm -f $(OBJ) $(NAME)

re: clean all