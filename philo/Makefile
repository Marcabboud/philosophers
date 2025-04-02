# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabboud <mabboud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 02:21:16 by mabboud           #+#    #+#              #
#    Updated: 2025/04/02 03:13:38 by mabboud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c src/ft_init.c src/utils.c\
 src/ft_simulation.c src/ft_args.c src/ft_actions.c

OBJ = $(SRC:.c=.o)
NAME = philo
HEADER = philo.h

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
		$(CC) $(FLAGS) $(OBJ) -pthread -o $(NAME)

%.o : %.c
		$(CC) $(FLAGS) -c -o $@ $^

clean :
		$(RM) $(OBJ) $(BOBJ)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
