/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 14:03:03 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/07 19:19:46 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_polygon(int **plots, t_game  *game, int edge)
{
	int i;

	i = 0;
	while (i < edge - 1)
		line(game, plots[i++], plots[i + 1]);
	line(game, plots[0], plots[i]);
}

void invert_y(int **plots, int edge)
{
	int i;

	i = 0;
	while (i < edge)
		plots[i++][1] = -plots[i][1];
}

void invert_z(int **plots, int edge)
{
	int i;

	i = 0;
	while (i < edge)
		plots[i++][2] = -plots[i][2];
}

float **vertex_matrix(t_object *object)
{
	float **vertex_m;

	vertex_m = alloc_2df(3,3);
	vertex_m[0][0] = cos(DEG_TO_RAD(object->angle));
	vertex_m[0][1] = vertex_m[1][2] = vertex_m[1][0] = 0;
	vertex_m[0][2] = sin(DEG_TO_RAD(object->angle));
	vertex_m[1][1] = 1;
	vertex_m[2][1] = 0; 
	vertex_m[2][0] = -sin(DEG_TO_RAD(object->angle));
	vertex_m[2][2] = cos(DEG_TO_RAD(object->angle));
	return(vertex_m);
}

void multiplication_m(t_object *object, int vectors_num)
{
	float **vertex_m;
	int i;
	float x_new;
	float y_new;
	float z_new;

	i = 0;
	vertex_m = vertex_matrix(object);
	while (i < vectors_num)
	{
		x_new = object->original_m[i][0] * vertex_m[0][0] + object->original_m[i][1] * vertex_m[1][0] + object->original_m[i][2] * vertex_m[2][0] + object->dx;
		y_new = object->original_m[i][0] * vertex_m[0][1] + object->original_m[i][1] * vertex_m[1][1] + object->original_m[i][2] * vertex_m[2][1] + object->dy;
		z_new = object->original_m[i][0] * vertex_m[0][2] + object->original_m[i][1] * vertex_m[1][2] + object->original_m[i][2] * vertex_m[2][2];
		object->multiplex_m[i][0] = object->distance * x_new/z_new;
		object->multiplex_m[i][1] = object->distance * y_new/z_new;
		object->multiplex_m[i][2] = z_new;
		printf("vector\nx %i\ny %i\nz %i\n", object->multiplex_m[i][0], object->multiplex_m[i][1], object->multiplex_m[i][2]);
		i++;
	}
}

int main()
{
	int		y = 0;
	int 	**face;
	int 	**top;
	int 	**right;
	int 	***figure;
	t_game game;
	t_object object;
	t_object object2;
	unsigned int		color = 0xFFFFFFFF;
	
	figure = malloc(sizeof(int **) * 3);
	if((face = alloc_2d(4, 3)) == 0)
		return (0);
	face[1][0] = -70;
	face[1][1] = -30;
	face[1][2] = 100;
	face[2][0] = -70;
	face[2][1] = 30;
	face[2][2] = 100;
	face[3][0] = 70;
	face[3][1] = 30;
	face[3][2] = 100;
	face[0][0] = 70;
	face[0][1] = -30;
	face[0][2] = 100;

	invert_y(face, 4);
	invert_z(face, 4);

	object.distance = 100;
	object.original_m = face;
	object.angle = 0;
	object.dx = 0;
	object.dy = 0;
	object.multiplex_m = object.original_m;
	multiplication_m(&object, 4);
	game.mlx_init = mlx_init();
	game.window = mlx_new_window(game.mlx_init, 900, 900, "hello world");
	game.img = mlx_new_image (game.mlx_init, 900, 900);
	game.strt_img = mlx_get_data_addr(game.img, &game.bppx, &game.len_of_line, &game.endian);
	game.center_img= &game.strt_img[((900 / 2) * (game.bppx / 8)) + ((900 / 2) * game.len_of_line)];
	game.color = color;
	game.edge = 6;
//	printf("%i\n", plots[0][0]);
//	rotate_triangle(plots, DEG_TO_RAD(270));
	print_polygon(object.multiplex_m, &game, 4);

	if((top = alloc_2d(4, 3)) == 0)
		return (0);
	top[1][0] = -70;
	top[1][1] = -30;
	top[1][2] = 100;
	top[2][0] = -70;
	top[2][1] = 30;
	top[2][2] = 100;
	top[3][0] = 70;
	top[3][1] = 30;
	top[3][2] = 100;
	top[0][0] = 70;
	top[0][1] = -30;
	top[0][2] = 100;
	object2.distance = 100;
	object2.original_m = top;
	object2.angle = 0;
	object2.dx = -140;
	object2.dy = 0;
	object2.multiplex_m = object2.original_m;
	invert_y(top, 4);
	invert_z(top, 4);
	object2.angle = -10;
	multiplication_m(&object2, 4);
	print_polygon(object2.multiplex_m, &game, 4);

//	background(&game, 200, 200, 0x01FF0000);
	mlx_put_image_to_window (game.mlx_init, game.window, game.img, 0, 0);
//	mlx_key_hook(game.window, key_win, &game);
//	mlx_mouse_hook(game.window, mouse_win, &game);
//	rotate_triangle(plots, DEG_TO_RAD(10));
//	print_triangle(game.strt_img, plots, 0x01FF0000);

	game.x = 0;
	game.y = 0;
	mlx_loop(game.mlx_init);
}