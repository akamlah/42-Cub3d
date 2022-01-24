# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 14:46:21 by akamlah           #+#    #+#              #
#    Updated: 2022/01/24 18:14:00 by akamlah          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

CFILES = ft_atoi.c ft_toupper.c ft_tolower.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memmove.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c \
ft_putnbr_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_putendl_fd.c ft_strmapi.c \
ft_putnbr_chex_fd.c ft_putnbr_hex_fd.c ft_atohex.c \
get_next_line.c \
ft_putarr_2d_fd.c \
ft_get_first_word.c \
ft_free_char2.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c

OFILES := $(patsubst %.c, %.o, $(CFILES))

all:
	@ make $(NAME)

$(NAME): $(OFILES) libft.h
	@ ar -rc $(NAME) $(OFILES) ; echo "Creating archive '$(NAME)'"

%.o : %.c
	@ $(CC) $(CFLAGS) $^ -c -o $@

.PHONY: clean

clean:
	@ /bin/rm -f $(OFILES)

fclean: clean
	@ echo "Removing libft.a"
	@ /bin/rm -f $(NAME)

re: fclean all
