# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 16:35:33 by opdi-bia          #+#    #+#              #
#    Updated: 2024/09/25 15:59:11 by opdi-bia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc -g 
CFLAGS=-Wall -Wextra -Werror 
SRC=main.c\
	parsing.c\
	utils_minishell.c\
	split.c\

OBJ=$(SRC:.c=.o)
NAME=minishell

.PHONY: all clean fclean re

all : $(NAME)

%.o: %.c
		$(CC) -c $(CFLAGS) $<
		
$(NAME): $(OBJ)
		$(CC) $(OBJ) -o $(NAME) -lreadline

clean:
	rm -f $(OBJ) $(OBJALL)
	rm -f *.out

fclean: clean
	rm -f $(NAME)

re: fclean all