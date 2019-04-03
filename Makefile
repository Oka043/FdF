# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaktion <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/23 18:36:58 by olaktion          #+#    #+#              #
#    Updated: 2018/08/23 18:37:01 by olaktion         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	fdf	

SRC =	line.c\
		main.c\
		act_map.c\
		act_struct.c\
		file_read.c\
		draw_line.c

INC = fdf.h

CFLAGS = -Wall -Wextra -Werror -I
OBJ =	$(SRC:.c=.o)
LIB = ./libft/

MLX = -lmlx -framework AppKit -framework OpenGl -O3

DIR_H = ./includes/

all: $(NAME)

makelib:
	make -C ./libft/

libclean:
	make -C ./libft/ clean

libfclean:
	make -C ./libft/ fclean

$(NAME): $(OBJ) makelib
	gcc -I $(INC) $(OBJ) -o $(NAME) -L$(LIB) -lft $(MLX)

%.o: %.c
	gcc -I $(INC) -c $< -o $@

clean: libclean
	rm -f $(OBJ)

fclean: libfclean clean
	rm -f $(NAME)

re: fclean all

.NOTPARALLEL: all clean fclean re
.PHONY: all clean fclean re

