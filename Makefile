# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 16:35:33 by opdi-bia          #+#    #+#              #
#    Updated: 2024/09/27 17:39:30 by eburnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc -g 
CFLAGS=-Wall -Wextra -Werror 
SRC=main.c\
init.c\
	tokenizing.c\
	utils_tokenizing.c\
	utils_minishell.c\
	signal.c\
	token_identify.c\
	exit.c\
	command_identify.c\
	

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
