/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 19:56:07 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/07 17:10:46 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_line(t_game  *game, t_line line, int size)
{
	while(size != -1)
	{
		if(line.y < 100 && line.y > -100 && line.x < 100 && line.x > -100)
			print_img_pxl(&game->center_img[line.x * 4 + (game->len_of_line * line.y)], game->color);
		line.error = line.error + line.deltaerr;
		while (line.error > line.deltax + 1)
		{
			line.y = line.y + line.diry;
			if(line.y < 100 && line.y > -100 && line.x < 100 && line.x > -100)
				print_img_pxl(&game->center_img[line.x * 4 + (game->len_of_line * line.y)], game->color);
			line.error = line.error - (line.deltax + 1);
		}
		size--;
		line.x += line.dirx;
	}
}

void	line(t_game  *game, int *vector1, int *vector2)
{
	t_line line;
	
	line.deltax = abs(vector2[0] - vector1[0]);
	line.error = 0;
	line.deltaerr = abs(vector2[1] - vector1[1]) + 1;
	line.y = vector1[1];
	line.x = vector1[0];
	line.diry = vector2[1] - vector1[1];
	if (line.diry > 0)
		line.diry = 1;
	if (line.diry < 0)
		line.diry = -1;
	line.dirx = vector2[0] - vector1[0];
	if (line.dirx > 0)
		line.dirx = 1;
	if (line.dirx < 0)
		line.dirx = -1;
	print_line(game, line, line.deltax);
}

void print_img_pxl(char *img, unsigned int color)
{
	int i = 4;

	while(i--)
	{
		*img++ = color;
		color = color >> 8;
	}
}

void background(t_game *game, int max_y, int max_x, unsigned int color)
{
	int x = 0;
	int y;
	while (x < max_x)
	{
		y = 0;
		while (y < max_y)
		{
			print_img_pxl(&game->strt_img[(y * 4) + (game->len_of_line * x)], color);
			y++;
		}
		x++;
	}
}


static void vector_x(char *start_img, unsigned int color, int *plot_1, int *plot_2)
{
	
	double k;
	double b;
	int y;
	int x;
	int *buf;

	if (plot_1[0] > plot_2[0])
	{
		buf = plot_1;
		plot_1 = plot_2;
		plot_2 = buf;
	}
	k =  ((float)plot_1[1] - (float)plot_2[1]) / ((float)plot_1[0] - (float)plot_2[0]);
	b = plot_1[1] - (k * plot_1[0]);
	x = plot_1[0];
	while(x < plot_2[0])
	{
		y = (int)ceil(x * k + b);
		if (x < 100 && x > -100 && y < 100 && y > -100)
			print_img_pxl(&start_img[(x * 4) + y * 800], color);
		x++;
	}
}

static	void vector_y(char *start_img, unsigned int color, int *plot_1, int *plot_2)
{
	double k;
	double b;
	int y;
	int x;
	int *buf;

	if (plot_1[1] > plot_2[1])
	{
		buf = plot_1;
		plot_1 = plot_2;
		plot_2 = buf;
	}
	if ((plot_1[0] - plot_2[0]) == 0)
		k = 0;
	else
		k =  ((float)plot_1[1] - (float)plot_2[1]) / ((float)plot_1[0] - (float)plot_2[0]);
	b = plot_1[1] - (k * plot_1[0]);
	y = plot_1[1];
	while(y < plot_2[1])
	{
		if (k) 
			x = (int)ceil((y - b) / k);
		else
			x = plot_1[0];
		if (x < 100 && x > -100 && y < 100 && y > -100)
			print_img_pxl(&start_img[(x * 4) + y * 800], color);
		y++;
	}
}

int** alloc_2d(int m, int n)
{
    int** arr;
    int i;
   
	i = 0;
    if ((arr = malloc(m * sizeof(*arr))) == 0)
		return (NULL);
    while (i < m)
        if((arr[i++] = malloc(n * sizeof(**arr))) == 0)
			return(NULL);
    return (arr);
}

float** alloc_2df(int m, int n)
{
    float** arr;
    int i;
   
	i = 0;
    if ((arr = malloc(m * sizeof(*arr))) == 0)
		return (NULL);
    while (i < m)
        if((arr[i++] = malloc(n * sizeof(**arr))) == 0)
			return(NULL);
    return (arr);
}

void print_vector(char *start_img, unsigned int color, int *plot_1, int *plot_2)
{
	if (abs(plot_1[0] - plot_2[0]) > abs(plot_1[1] - plot_2[1]))
	{
		vector_x(start_img, color, plot_1, plot_2);
	}
	else
		vector_y(start_img, color, plot_1, plot_2);
}