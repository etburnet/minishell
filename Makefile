# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opdi-bia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 16:35:33 by opdi-bia          #+#    #+#              #
#    Updated: 2024/10/21 18:35:35 by opdi-bia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRC=main.c\
	utils_minishell.c\
	signal.c\
	shlvl.c\
	parsing/init.c\
	parsing/tokenizing.c\
	parsing/utils_tokenizing.c\
	parsing/set_line.c\
	parsing/token_identify.c\
	parsing/utils_token_identify.c\
	parsing/command_identify.c\
	parsing/command_utils.c\
	parsing/utils_cmd_identify.c\
	parsing/expand.c\
	parsing/expand_utils.c\
	parsing/in_out_check.c\
	parsing/search_cmd.c\
	parsing/set_line_utils.c\
	builtins/env.c\
	builtins/pwd.c\
	builtins/echo.c\
	builtins/cd.c\
	builtins/exit.c\
	builtins/export.c\
	builtins/export_utils.c\
	builtins/unset.c\
	builtins/utils_builtins.c\
	execution/execution_utils2.c\
	execution/execution.c\
	execution/execution_utils.c\
	execution/execution_builtins.c\
	execution/here_doc.c\
	
OBJS = $(SRC:.c=.o)
HEADERS = minishell.h
LIBFT_PATH = ./libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)/libft.a
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft -o $(NAME) -lreadline

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) $< -o $@

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(OBJS)
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all