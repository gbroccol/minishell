# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 13:22:23 by gbroccol          #+#    #+#              #
#    Updated: 2020/11/13 17:47:51 by gbroccol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= proga
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
				parsing/arguments.c \
				parsing/quote.c \
				parsing/redirect.c \
				parsing/check_gnl_line.c \
				parsing/env.c \
				launch/execute.c \
				launch/shell_cd_pwd.c \
				launch/shell_echo.c \
				launch/shell_env_unset.c \
				launch/shell_exit.c \
				launch/shell_export.c \
				launch/launch.c \
				launch/find_path.c \
				launch/export_utils.c \
				exit.c
					
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