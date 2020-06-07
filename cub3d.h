/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:03:51 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/07 17:11:39 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define DEG_TO_RAD(deg) (M_PI*deg/180)
#define RAD_TO_DEG(rad) (M_PI*deg/180)


typedef struct	s_object
{
	int **original_m;
	float angle;
	int dx;
	int dy;
	float scale;
	int **multiplex_m;
	
}				t_object;

typedef struct	s_game
{
	char *strt_img;
	char *center_img;
	void *mlx_init;
	int ***figure;
	void *window;
	void *img;
	int		len_of_line;
	int		bppx;
	int		edge;
	int		endian;
	unsigned int color;
	int x;
	int y;
	t_object object;

}				t_game;



/*
typedef struct s_matrix
{
	float elem[3][3];
}				t_matrix;
*/
typedef struct	s_line
{
	int deltax;
	int error;
	int deltaerr;
	int y;
	int x;
	int diry;
	int dirx;
}				t_line;

void print_img_pxl(char *img, unsigned int color);
void background(t_game *game, int max_y, int max_x, unsigned int color);
void print_vector(char *start_img, unsigned int color, int *plot_1, int *plot_2);
void	line(t_game  *game, int *vector1, int *vector2);
int		**alloc_2d(int m, int n);
float** alloc_2df(int m, int n);

