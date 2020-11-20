# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 13:22:23 by gbroccol          #+#    #+#              #
#    Updated: 2020/11/20 16:57:39 by pvivian          ###   ########.fr        #
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
				parse_and_exec.c \
				parsing/clear.c \
				parsing/save_env.c \
				parsing/parsing.c \
				parsing/command.c \
				parsing/dollar_no.c \
				parsing/dollar_two.c \
				parsing/arguments.c \
				parsing/quote_no.c \
				parsing/quote_one.c \
				parsing/quote_two.c \
				parsing/redirect.c \
				parsing/check_gnl_line.c \
				parsing/check_err_share_smb.c \
				parsing/check_err_red_smb.c \
				parsing/check_redir_files.c \
				parsing/env.c \
				launch/execute.c \
				launch/shell_cd.c \
				launch/shell_pwd.c \
				launch/shell_echo.c \
				launch/shell_env_unset.c \
				launch/shell_exit.c \
				launch/shell_export.c \
				launch/launch.c \
				launch/processes.c \
				launch/find_path.c \
				launch/export_utils.c \
				launch/check_env.c \
				launch/export_new_env.c \
				launch/replace_env.c \
				launch/fd_redirection.c \
				launch/check_redir.c \
				launch/utils.c \
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

.PHONY: all clean fclean re libft_all libft_clean libft_fclean test
