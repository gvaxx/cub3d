# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/29 16:16:54 by mcaptain          #+#    #+#              #
#    Updated: 2020/06/29 16:34:45 by mcaptain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

NAME = cub3d

SRCS =	utils/get_next_line.c \
		utils/get_next_line_utils.c \
		engine/main.c engine/raycasting.c \
		engine/count_distance.c \
		utils/utils_raycasting2.c \
		utils/utils_raycasting.c \
		engine/sprite.c \
		engine/key_handler.c \
		engine/map.c \
		engine/comparison_distance.c \
		engine/first_frame.c \
		engine/cub_parser.c \
		engine/error.c \
		engine/bmp.c \
		engine/destroyer.c 

INCLUDE = -Iinclude
OBJS = $(SRCS:.c=.o)

FRAMEWORKS = -framework OpenGL -framework AppKit
LIBRARIES = utils/libft.a utils/libmlx.a

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBRARIES) $(FRAMEWORKS)

%.o: %.c
	gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

linux: 
	gcc -Iinclude -fsanitize=address utils/get_next_line.c utils/get_next_line_utils.c engine/main.c engine/raycasting.c engine/count_distance.c utils/utils_raycasting2.c utils/utils_raycasting.c engine/sprite.c engine/key_handler.c engine/map.c engine/comparison_distance.c engine/first_frame.c engine/cub_parser.c engine/error.c engine/bmp.c engine/destroyer.c utils/libft.a utils/libmlx.a -lmlx -lX11 -lXext -lm  