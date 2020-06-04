/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 19:56:07 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/04 20:00:05 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void print_vector(char *start_img, unsigned int color, int *plot_1, int *plot_2)
{
	if (abs(plot_1[0] - plot_2[0]) > abs(plot_1[1] - plot_2[1]))
	{
		vector_x(start_img, color, plot_1, plot_2);
	}
	else
		vector_y(start_img, color, plot_1, plot_2);
	
}