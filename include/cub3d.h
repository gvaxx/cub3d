/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:03:51 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/25 15:07:08 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H
# define MALLOC_MAP_ERROR -1
# define HANDLE_MAP_ERROR -2
# define PARSE_CUB_ERROR -3
# define WITHOUT_ARG_ERROR -4
# define WRONG_NUM_ARG -5
# define WRONG_ARG -6
# define TEXTURE_FAILED -7
# define MAX_WIDTH 1600
# define MAX_HEIGHT 900
# define PI2 3.14159/2
# define PI3 3*3.14159/2
# define DR M_PI/180
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

typedef struct	s_sprite
{
	float	dist;
	int		x;
	int		y;
}				t_sprite;

typedef struct	s_image
{
	void			*img;
	unsigned char	*strt_img;
	int				len_of_line;
	int				bppx;
	int				endian;
	int				width;
	int				height;
}				t_image;

typedef struct	s_info
{
	int		resolution_x;
	int		resolution_y;
	char	*texture_no;
	char	*texture_so;
	char	*texture_ea;
	char	*texture_we;
	char	*texture_sprite;
	int		color_floor;
	int		color_ceil;
	char	**map;
	int		map_width;
	int		map_height;
}				t_info;

typedef struct	s_game
{
	void		*mlx_init;
	void		*window;
	t_image		main_img;
	int			px;
	int			py;
	float		pa;
	float		pdx;
	float		pdy;
	float		prlx;
	float		prly;
	float		rax;
	t_sprite	*sprites_array;
	size_t		sprites_num;
	t_image		texture_no;
	t_image		texture_so;
	t_image		texture_ea;
	t_image		texture_we;
	t_image		texture_sprite;
	t_info		game_info;
}				t_game;

typedef struct	s_param
{
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	int		dof;
}				t_param;

typedef struct	s_distance
{
	float	x;
	float	y;
	float	dist;
	int		mx;
	int		my;
	int		mp;
}				t_distance;

typedef struct	s_tech
{
	float	sprite_dir;
	size_t	sp_h;
	size_t	sp_w;
	int		sp_dw;
	int		sp_dh;
}				t_tech;

typedef struct	s_line
{
	float			dist;
	float			x_percent;
	unsigned char	*start_texture;
	t_image			*texture;
	float			ra;
}				t_line;

void			fill_x_params(t_game *game, t_param *x_param, float ra);
float			is_full_circle(float ra);
void			replace_pixel(unsigned char *convert_img,
unsigned char *source_img);
float			dist(float ax, float ay, float bx, float by);
void			fill_y_params(t_game *game, t_param *y_param,
float ra);
void			count_y_distance(t_param *y_param, t_game *game,
float ra, t_distance *y_distance);
void			count_x_distance(t_param *x_param, t_game *game,
float ra, t_distance *x_distance);
float			dist(float ax, float ay, float bx, float by);
void			print_img_pxl(char *img, unsigned int color);
void			background(t_game *game, int max_y, int max_x,
unsigned int color);
void			print_vector(char *start_img, unsigned int color, int
*plot_1, int *plot_2);
int				map_manager(int fd, char *line, t_info *game_info);
void			line(t_game *game, int *vector1, int *vector2);
t_game			*window_init(t_info *game_info);
void			print_ceil(int x, int y, int length, t_game *game);
void			print_floor(int x, int y, int length, t_game *game);
void			sprite_handler(t_game *game, float *depth_buffer);
void			bias(t_game *game);
int				key_win(int key, t_game *game);
void			drawrays3d(t_game *game);
int				is_in_set(char c, char const *set);
void			find_player_position(t_game *game);
void			find_sprites(t_game *game);
void			num_sprites(t_game *game);
void			count_y_distance(t_param *y_param, t_game *game, float ra,
t_distance *y_distance);
void			count_less_distance(t_distance *y_distance,
t_distance *x_distance, t_line *line, t_game *game);
int				color_handler(char *line);
int				cub_file_parser(char *line, int fd, t_info *game_info);
int				resolution_handler(char *line, t_info *game_info);
char			*next_number(char *line);
void			distance_handler(t_game *game, t_line *line);
int				error_handler(int error_num);
void			destroy_game(t_game *game);

#endif
