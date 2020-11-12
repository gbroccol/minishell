# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 13:22:23 by gbroccol          #+#    #+#              #
#    Updated: 2020/11/12 13:40:09 by pvivian          ###   ########.fr        #
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
				parsing/cmd_quote_no.c \
				parsing/cmd_quote_one.c \
				parsing/cmd_quote_two.c \
				parsing/arguments.c \
				parsing/quote_no.c \
				parsing/quote_one.c \
				parsing/quote_two.c \
				parsing/check_redirect.c \
				parsing/check_flags.c \
				parsing/check_gnl_line.c \
				parsing/is_env.c \
				parsing/check_env.c \
				parsing/check_shielding.c \
				parsing/create_bin_tok.c \
				parsing/error.c \
				launch/execute.c \
				launch/shell_cd_pwd.c \
				launch/shell_echo.c \
				launch/shell_env_unset.c \
				launch/shell_exit.c \
				launch/shell_export.c \
				launch/launch.c \
				launch/find_path.c \
				launch/export_utils.c
					
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