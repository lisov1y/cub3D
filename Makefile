# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mike <mike@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 16:35:56 by mike              #+#    #+#              #
#    Updated: 2020/05/08 20:16:59 by mike             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = main.c

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wall -Werror -Wextra

MLX = minilibx/libmlx.a -lm -lX11 -lXext

R= \033[0;31m

G= \033[0;32m

W = \033[0m

all: $(NAME)

$(NAME):
	@cd Libft && make -s
	@gcc -c $(SRC) $(FLAGS)
	@gcc $(OBJ) $(MLX) -o $(NAME)
	@echo "$(G)The game is ready to play!$(W)"

clean:
	@cd Libft && make -s clean
	@rm -rf $(OBJ)
	@echo "$(G)Object files deleted.$(W)"

fclean: clean
	@cd Libft && rm -rf libft.a
	@echo "$(R)libft.a $(G)deleted.$(W)"
	@rm -rf $(NAME)
	@echo "$(G)Game executable deleted.$(W)"

re: fclean all