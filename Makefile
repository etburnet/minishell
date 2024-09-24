# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 12:48:48 by eburnet           #+#    #+#              #
#    Updated: 2024/06/07 11:42:56 by eburnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -Wall -Wextra -Werror -g3
SRCS = main.c ft_execute.c ft_utils.c ft_search.c
OBJS = $(SRCS:.c=.o)
HEADERS = pipex.h
LIBFT_PATH = ./libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)/libft.a
	cc $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -o $(NAME)

%.o: %.c $(HEADERS)
	cc $(CFLAGS) -c $< -o $@

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
=======
#    By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 16:35:33 by opdi-bia          #+#    #+#              #
#    Updated: 2024/09/23 16:41:01 by opdi-bia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc -g 
CFLAGS=-Wall -Wextra -Werror 
SRC=main.c\
	parsing.c\
	utils_minishell.c\

OBJ=$(SRC:.c=.o)
NAME=minisehll

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
>>>>>>> pipex
