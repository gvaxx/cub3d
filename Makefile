all: 
	gcc -Iinclude -fsanitize=address utils/get_next_line.c utils/get_next_line_utils.c engine/main.c engine/raycasting.c engine/count_distance.c utils/utils_raycasting2.c utils/utils_raycasting.c engine/sprite.c engine/key_handler.c engine/map.c engine/comparison_distance.c engine/first_frame.c engine/cub_parser.c engine/error.c engine/bmp.c engine/destroyer.c utils/libft.a utils/libmlx.a -lmlx -lX11 -lXext -lm  