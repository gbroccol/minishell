# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 13:22:23 by gbroccol          #+#    #+#              #
#    Updated: 2020/10/15 13:22:25 by gbroccol         ###   ########.fr        #
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
				parsing/parsing.c \
				launch/launch.c \
				launch/execute.c		
OBJ			= $(SRC:.c=.o)

all: libft_all $(NAME)
$(NAME): $(OBJ)
	@$(CC) libft.a -I./ $(OBJ) -o $@
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