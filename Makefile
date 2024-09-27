# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 16:35:33 by opdi-bia          #+#    #+#              #
#    Updated: 2024/09/27 10:42:21 by eburnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRC=main.c\
	parsing.c\
	utils_minishell.c\
	builtins/env.c\
	builtins/pwd.c\
	builtins/echo.c\
	builtins/cd.c\
	builtins/exit.c\
	builtins/export.c\
	builtins/shlvl.c\
	
OBJS = $(SRC:.c=.o)
HEADERS = minishell.h
LIBFT_PATH = ./libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)/libft.a
	cc $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft -o $(NAME) -lreadline

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

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