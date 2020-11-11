# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 13:22:23 by gbroccol          #+#    #+#              #
#    Updated: 2020/11/01 17:58:39 by pvivian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIBFT_PATH	= ./libft
LIBFT		= libft
INCLUDE		= minishell.h
CC			= gcc -g -Wall -Wextra -Werror
RM			= rm -rf

SRC			= \
				main.c \
				parsing/clear.c \
				parsing/parsing.c \
				parsing/command.c \
				parsing/command_test.c \
				parsing/cmd_quote_no.c \
				parsing/cmd_quote_one.c \
				parsing/cmd_quote_two.c \
				parsing/arguments.c \
				parsing/quote_no.c \
				parsing/quote_one.c \
				parsing/quote_two.c \
				parsing/check_redirect.c \
				parsing/check_gnl_line.c \
				parsing/is_env.c \
				parsing/check_env.c \
				parsing/check_shielding.c \
				parsing/create_bin_tok.c \
				parsing/error.c \
				launch/execute.c \
				launch/launch.c
					
OBJ			= $(SRC:.c=.o)

all: libft_all $(NAME)
$(NAME): $(OBJ)
	@$(CC) -I./ $(OBJ) libft.a -o $@
clean: libft_clean
	@$(RM) $(NAME)
fclean: libft_fclean clean
	@$(RM) $(OBJ)
re: fclean all

libft_all:
	make -C $(LIBFT_PATH) all
	cp ./libft/libft.a libft.a
libft_clean:
	make -C $(LIBFT_PATH) clean
libft_fclean:
	make -C $(LIBFT_PATH) fclean
	$(RM) libft.a

test: all
	@./minishell

.PHONY: all clean fclean re