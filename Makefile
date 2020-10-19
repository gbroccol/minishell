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

# OS			= $(shell uname)

NAME		= minishell
LIBFT_PATH	= ./libft
LIBFT		= libft

INCLUDE		= minishell.h

# ifeq ($(OS), Linux)
# 			FLAGS = -f elf64
# else
# 			FLAGS = -f macho64
# endif

CC			= gcc -g -Wall -Wextra -Werror

RM			= rm -rf

SRC = 
OBJ			= $(SRC:.s=.o)

# %.o : %.s
# 	@$(ASM) $(FLAGS) -s $< -o $@

all: libft_all $(NAME)

$(NAME): $(OBJ)
	@$(CC)  $(NAME) libft.a -I./ $(OBJ) -o $@

clean: libft_clean
	@$(RM) $(NAME)

fclean: libft_fclean clean
	@$(RM) $(NAME)

re: fclean all


libft_all:
	make -C $(LIBFT_PATH) all
	cp ./libft/libft.a libft.a

libft_clean:
	make -C $(LIBFT_PATH) clean

libft_fclean:
	make -C $(LIBFT_PATH) fclean
	$(RM) libft.a

# test: re
# 	$(GCC) $(GCCFLAGS) main.c -L. -lasm
# 	./a.out

.PHONY: all clean fclean re

