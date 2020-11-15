# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvivian <pvivian@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/29 21:32:03 by anastasiya        #+#    #+#              #
#    Updated: 2020/10/27 15:04:29 by pvivian          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = /.
FLAGS = -Wall -Werror -Wextra
FUNC_MAIN.c = \
	ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_memccpy.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strlen_n.c\
	ft_strmapi.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c\
	get_next_line.c\
	ft_strncmp_no_cases.c \
	is_smb_in_str.c \
	ft_letter_to_str.c \
	ft_str_to_str.c \
	ft_free_array.c \
	ft_str_to_array.c \
	ft_del_str_from_ar.c \
	if_smb_in_str.c \
	ft_strdup_start.c \
	bzero_array.c \
	ft_sort_array.c \
	ft_array_len.c

FUNC_BONUS.c = \
	ft_lstnew.c\
	ft_lstadd_front.c\
	ft_lstsize.c\
	ft_lstlast.c\
	ft_lstadd_back.c\
	ft_lstdelone.c\
	ft_lstclear.c\
	ft_lstiter.c\
	ft_lstmap.c

MAIN_OBJ_FILES = \
	ft_atoi.o\
	ft_bzero.o\
	ft_calloc.o\
	ft_isalnum.o\
	ft_isalpha.o\
	ft_isascii.o\
	ft_isdigit.o\
	ft_isprint.o\
	ft_itoa.o\
	ft_memccpy.o\
	ft_memchr.o\
	ft_memcmp.o\
	ft_memcpy.o\
	ft_memmove.o\
	ft_memset.o\
	ft_putchar_fd.o\
	ft_putendl_fd.o\
	ft_putnbr_fd.o\
	ft_putstr_fd.o\
	ft_split.o\
	ft_strchr.o\
	ft_strdup.o\
	ft_strjoin.o\
	ft_strlcat.o\
	ft_strlcpy.o\
	ft_strlen.o\
	ft_strlen_n.o\
	ft_strmapi.o\
	ft_strcmp.o\
	ft_strncmp.o\
	ft_strnstr.o\
	ft_strrchr.o\
	ft_strtrim.o\
	ft_substr.o\
	ft_tolower.o\
	ft_toupper.o\
	get_next_line.o\
	ft_strncmp_no_cases.o \
	is_smb_in_str.o \
	ft_letter_to_str.o \
	ft_str_to_str.o \
	ft_free_array.o \
	ft_str_to_array.o \
	ft_del_str_from_ar.o \
	if_smb_in_str.o \
	ft_strdup_start.o \
	bzero_array.o \
	ft_sort_array.o \
	ft_array_len.o

BONUS_OBJ_FILES = \
	ft_lstnew.o\
	ft_lstadd_front.o\
	ft_lstsize.o\
	ft_lstlast.o\
	ft_lstadd_back.o\
	ft_lstdelone.o\
	ft_lstclear.o\
	ft_lstiter.o\
	ft_lstmap.o

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(MAIN_OBJ_FILES)
	@ar rc $(NAME) $(MAIN_OBJ_FILES)
	@ranlib $(NAME)

bonus: $(BONUS_OBJ_FILES) $(MAIN_OBJ_FILES)
	@ar rc $(NAME) $(BONUS_OBJ_FILES) $(MAIN_OBJ_FILES)
	@ranlib $(NAME)

%.o: %.c libft.h
	gcc -c $(FLAGS) -I $(HEADER) -o $@ $<

clean:
	@rm -f $(MAIN_OBJ_FILES) $(BONUS_OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all
