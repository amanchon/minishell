# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanchon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/16 14:26:06 by amanchon          #+#    #+#              #
#    Updated: 2020/01/16 14:26:21 by amanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =			ft_atoi.c\
				ft_split.c\
                ft_strdup.c\
                ft_isdigit.c\
                ft_strjoin.c\
                ft_isalpha.c\
                ft_strlcat.c\
                ft_isascii.c\
                ft_strlcpy.c \
                ft_isalnum.c\
                ft_strlen.c\
                ft_isprint.c\
                ft_strncmp.c\
                ft_putendl_fd.c\
                ft_putnbr_fd.c\
                ft_tolower.c\
                ft_putstr_fd.c\
                ft_toupper.c\
				ft_memset.c\
				ft_bzero.c\
				ft_memcpy.c\
				ft_memccpy.c\
				ft_memmove.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_calloc.c\
				ft_itoa.c\
				ft_strchr.c\
				ft_strrchr.c\
				ft_strnstr.c\
				ft_substr.c\
				ft_strtrim.c\
				ft_strmapi.c\
				ft_putchar_fd.c\
				ft_atoll.c\
				ft_ctostr.c\
				ft_insert_str.c\
				ft_strmcat.c\
				ft_strmcatn.c\
				get_next_line.c\
				free_dtab.c\
				ft_dtabdup.c \
				ft_atoull.c\

FLAGS = -Wall -Werror -Wextra

CC = gcc

SRC_O = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC_O)
		$(CC) $(FLAGS) -c $(SRC)
		ar rcs $(NAME) $(SRC_O)

clean:
	rm -rf  $(SRC_O)

fclean: clean
		rm -rf $(NAME)

re: 	fclean all clean

cleanall: 
	rm *.o *.a a.out
