# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 22:23:55 by amanchon          #+#    #+#              #
#    Updated: 2020/11/17 22:53:33 by amanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDE = ./srcs/minishell.h
CFLAGS = -Wall -Wextra -Werror -ltermcap -lncurses -fsanitize=address -g3

UTILS_SRCS = 	./srcs/utils.c \
				./srcs/utils2.c \
				./srcs/utils3.c \
				./srcs/utils4.c \
				./srcs/utils_pipes.c \
				./srcs/utils_redi.c \

SRCS =			./srcs/main.c \
				./srcs/builtin_cd.c \
				./srcs/builtins_env.c \
				./srcs/export_unset.c \
				./srcs/input_change.c \
				./srcs/input_insert.c \
				./srcs/checknfill_env.c \
				./srcs/error.c \
				./srcs/error2.c \
				./srcs/exec.c \
				./srcs/cmd.c \
				./srcs/ft_echo.c \
				./srcs/history.c \
				./srcs/interpret_line.c \
				./srcs/interpret_line2.c \
				./srcs/interpret_var.c \
				./srcs/mark_var.c \
				./srcs/joker.c \
				./srcs/pipes.c \
				./srcs/read_n_treat.c \
				./srcs/redirections.c \
				./srcs/signal.c \
				./srcs/ft_exit.c \

UTILS_OBJS = $(UTILS_SRCS:.c=.o)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(UTILS_OBJS) $(OBJS) $(INCLUDE)
	gcc -o $(NAME) $(OBJS) $(UTILS_OBJS) ${CFLAGS} -L./Libft -lft

clean:
	rm -f $(UTILS_OBJS) $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

rebonus : fclean bonus

main:
	gcc $(CFLAGS) main.c libftprintf.a
