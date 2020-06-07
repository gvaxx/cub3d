#include "cub3d.h"



void print_triangle(int **plots, t_game  *game)
{
	line(game, plots[0], plots[1]);
	line(game, plots[1], plots[2]);
	line(game, plots[0], plots[2]);
}

void plot_scale(int **plots, float size)
{
	int i;

	i = 0;
	while (i < 3)
		plots[i++][1] *= size;
	i = 0;
	while (i < 3)
		plots[i++][0] *= size;
}

void rotate_triangle(int **plots, float angle)
{
	double cs = cos(angle);
	double sn = sin(angle);
	double x_new;
	double y_new;
	int i = 0;
	while(i < 3)
	{
		x_new = (plots[i][0] * cs) - (plots[i][1] * sn);
		y_new = (plots[i][1] * cs) + (plots[i][0] * sn);
		plots[i][0] = (int)ceil(x_new);
		plots[i++][1] = (int)ceil(y_new);
	}

}

void shift_x(int **plot, int shift)
{
	int i;

	i = 0;
	while (i < 3)
		plot[i++][0] += shift;
}

void shift_y(int **plot, int shift)
{
	int i;

	i = 0;
	while (i < 3)
		plot[i++][1] += shift;
}

int	key_win(int key, t_game *game)
{	
	printf("Key in Win : %d\n",key);
	if (key == 119)
		shift_y(game->plot, -10);
	if (key == 115)
		shift_y(game->plot, 10);
	if (key == 97)
		shift_x(game->plot, -10);
	if (key == 100)
		shift_x(game->plot, 10);
	if (key == 101)
		rotate_triangle(game->plot, DEG_TO_RAD(-10));
	if (key == 113)
		rotate_triangle(game->plot, DEG_TO_RAD(10));
	background(game, 200, 200, 0);
	print_triangle(game->center_img, game->plot, game->color, game);
	mlx_put_image_to_window(game->mlx_init, game->window, game->img, 0, 0);	
}

int	mouse_win(int button, int x, int y, t_game *game)
{
	printf("Mouse in Win, button %d at %dx%d.\n",button,x,y);
	if (button == 1)
	{
		game->color = random();
		background(game, 200, 200, 0);
		print_triangle(game->center_img, game->plot, game->color, game);
		mlx_put_image_to_window(game->mlx_init, game->window, game->img, 0, 0);	
	}
	if (button == 4)
	{
		plot_scale(game->plot, 1.25);
		background(game, 200, 200, 0);
		print_triangle(game->center_img, game->plot, game->color, game);
		mlx_put_image_to_window(game->mlx_init, game->window, game->img, 0, 0);	
	}
	if (button == 5)
	{
		plot_scale(game->plot, 0.75);
		background(game, 200, 200, 0);
		print_triangle(game->center_img, game->plot, game->color, game);
		mlx_put_image_to_window(game->mlx_init, game->window, game->img, 0, 0);	
	}
	return(0);
}


int main()
{
	int		y = 0;
	int 	**plots;
	t_game game;
	unsigned int		color = 0xFFFFFFFF;
	
	if((plots = alloc_2d(3, 2)) == 0)
		return (0);
	plots[0][0] = 40;
	plots[0][1] = 30;
	plots[1][0] = 5;
	plots[1][1] = 3;
	plots[2][0] = 20;
	plots[2][1] = 50;
	game.plot = plots;
	game.mlx_init = mlx_init();
	game.window = mlx_new_window(game.mlx_init, 200, 200, "hello world");
	game.img = mlx_new_image (game.mlx_init, 200, 200);
	game.strt_img = mlx_get_data_addr(game.img, &game.bppx, &game.len_of_line, &game.endian);
	game.center_img= &game.strt_img[((200 / 2) * (game.bppx / 8)) + ((200 / 2) * game.len_of_line)];
	game.color = color;
//	printf("%i\n", plots[0][0]);
//	rotate_triangle(plots, DEG_TO_RAD(270));
	print_triangle(game.center_img, plots, 0xFFFFFFFF, &game);
//	background(&game, 200, 200, 0x01FF0000);
	mlx_put_image_to_window (game.mlx_init, game.window, game.img, 0, 0);
	mlx_key_hook(game.window, key_win, &game);
	mlx_mouse_hook(game.window, mouse_win, &game);
//	rotate_triangle(plots, DEG_TO_RAD(10));
//	print_triangle(game.strt_img, plots, 0x01FF0000);

	game.x = 0;
	game.y = 0;
	mlx_loop(game.mlx_init);
}