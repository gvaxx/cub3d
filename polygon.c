/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 11:29:48 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/07 12:56:52 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void print_polygon(int **plots, t_object  *object, int edge)
{
	int i;

	i = 0;
	while (i < edge - 1)
		line(object, plots[i++], plots[i + 1]);
	line(object, plots[0], plots[i]);
	printf("ok\n");
	printf("%i\n", i);
}

void plot_scale(int **plots, float size, int edge)
{
	int i;

	i = 0;
	while (i < edge)
		plots[i++][1] *= size;
	i = 0;
	while (i < edge)
		plots[i++][0] *= size;
}
/*
void rotate_triangle(int **plots, float angle, int edge)
{
	double cs = cos(angle);
	double sn = sin(angle);
	double x_new;
	double y_new;
	int i = 0;
	while(i < edge)
	{
		x_new = (plots[i][0] * cs) - (plots[i][1] * sn);
		y_new = (plots[i][1] * cs) + (plots[i][0] * sn);
		plots[i][0] = (int)ceil(x_new);
		plots[i++][1] = (int)ceil(y_new);
	}

}

void shift_x(int **plot, int shift, int edge)
{
	int i;

	i = 0;
	while (i < edge)
		plot[i++][0] += shift;
}

void shift_y(int **plot, int shift, int edge)
{
	int i;

	i = 0;
	while (i < edge)
		plot[i++][1] += shift;
}

int	key_win(int key, t_object *object)
{	
	printf("Key in Win : %d\n",key);
	if (key == 119)
		shift_y(object->plot, -10, object->edge);
	if (key == 115)
		shift_y(object->plot, 10, object->edge);
	if (key == 97)
		shift_x(object->plot, -10, object->edge);
	if (key == 100)
		shift_x(object->plot, 10, object->edge);
	if (key == 101)
		rotate_triangle(object->plot, DEG_TO_RAD(-10), object->edge);
	if (key == 113)
		rotate_triangle(object->plot, DEG_TO_RAD(10), object->edge);
	background(object, 200, 200, 0);
	print_polygon(object->plot, object, object->edge);
	mlx_put_image_to_window(object->mlx_init, object->window, object->img, 0, 0);	
}

int	mouse_win(int button, int x, int y, t_object *object)
{
	printf("Mouse in Win, button %d at %dx%d.\n",button,x,y);
	if (button == 1)
	{
		object->color = random();
		background(object, 200, 200, 0);
		print_polygon(object->plot, object, object->edge);
		mlx_put_image_to_window(object->mlx_init, object->window, object->img, 0, 0);	
	}
	if (button == 4)
	{
		plot_scale(object->plot, 1.25, object->edge);
		background(object, 200, 200, 0);
		print_polygon(object->plot, object, object->edge);
		mlx_put_image_to_window(object->mlx_init, object->window, object->img, 0, 0);	
	}
	if (button == 5)
	{
		plot_scale(object->plot, 0.75, object->edge);
		background(object, 200, 200, 0);
		print_polygon(object->plot, object, object->edge);
		mlx_put_image_to_window(object->mlx_init, object->window, object->img, 0, 0);	
	}
	return(0);
}*/

void invert_y(int **plots, int edge)
{
	int i;

	i = 0;
	while (i < edge)
		plots[i++][1] = -plots[i][1];
}

void print_figure(t_object *object, int face)
{
	int i;

	i = 0;
	while (i < face)
		print_polygon(object->figure[i++], object, 4);
}

int main()
{
	int		y = 0;
	int 	**face;
	int 	**top;
	int 	**right;
	int 	***figure;
	t_object object;
	unsigned int		color = 0xFFFFFFFF;
	
	figure = malloc(sizeof(int **) * 3);
	if((face = alloc_2d(4, 2)) == 0)
		return (0);
	if((top = alloc_2d(4, 2)) == 0)
		return (0);
	if((right = alloc_2d(4, 2)) == 0)
		return (0);
	face[0][0] = 0;
	face[0][1] = 0;
	face[1][0] = 0;
	face[1][1] = 10;
	face[2][0] = 10;
	face[2][1] = 10;
	face[3][0] = 10;
	face[3][1] = 0;
	invert_y(face, 4);
	top[0][0] = 0;
	top[0][1] = 10;
	top[1][0] = 5;
	top[1][1] = 12;
	top[2][0] = 15;
	top[2][1] = 12;
	top[3][0] = 10;
	top[3][1] = 10;
	invert_y(top, 4);
	right[0][0] = 10;
	right[0][1] = 0;
	right[1][0] = 10;
	right[1][1] = 10;
	right[2][0] = 15;
	right[2][1] = 12;
	right[3][0] = 15;
	right[3][1] = 2;
	invert_y(right, 4);

	figure[0] = face;
	figure[1] = top;
	figure[2] = right;
	object.figure = figure;
	object.mlx_init = mlx_init();
	object.window = mlx_new_window(object.mlx_init, 200, 200, "hello world");
	object.img = mlx_new_image (object.mlx_init, 200, 200);
	object.strt_img = mlx_get_data_addr(object.img, &object.bppx, &object.len_of_line, &object.endian);
	object.center_img= &object.strt_img[((200 / 2) * (object.bppx / 8)) + ((200 / 2) * object.len_of_line)];
	object.color = color;
	object.edge = 6;
//	printf("%i\n", plots[0][0]);
//	rotate_triangle(plots, DEG_TO_RAD(270));
	print_figure(&object, 3);
//	background(&object, 200, 200, 0x01FF0000);
	mlx_put_image_to_window (object.mlx_init, object.window, object.img, 0, 0);
//	mlx_key_hook(object.window, key_win, &object);
//	mlx_mouse_hook(object.window, mouse_win, &object);
//	rotate_triangle(plots, DEG_TO_RAD(10));
//	print_triangle(object.strt_img, plots, 0x01FF0000);

	object.x = 0;
	object.y = 0;
	mlx_loop(object.mlx_init);
}