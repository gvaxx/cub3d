#include  <mlx.h>
#include <stdlib.h>
#include "cub3d.h"



void print_cub(char *start_img, unsigned int color, int shift_x, int shift_y, int edge)
{
	int x = shift_x;
	int y;
	while (x < shift_x + edge && x < 100)
	{
		if (x > -1)
		{
			y = shift_y;
			while(y < shift_y + edge && y < 100)
			{
				if(y > -1)
					print_img_pxl(&start_img[(y * 4) + (400 * x)], color);
				y++;
			}
		}
		x++;
	}
}

int	mouse_win(int button,int x,int y, t_game *game)
{
	printf("Mouse in Win, button %d at %dx%d.\n",button,x,y);

	if (button == 1)
	{
	//	printf("%X\n", *ptr);
		game->color = random();
		background(game, 100, 100, 0);
		print_cub(game->strt_img, game->color, game->x, game->y, 20);
		printf("%X\n", game->color);
		mlx_put_image_to_window(game->mlx_init, game->window, game->img, 0, 0);
		return(1);
	}
	return(0);
}

int	key_win(int key,t_game *game)
{	
	printf("Key in Win : %d\n",key);
	if (key == 119)
		game->x -=10;
	if (key == 115)
			game->x +=10;
	if (key == 97)
			game->y -=10;
	if (key == 100)
			game->y +=10;
	background(game, 100, 100, 0);
	print_cub(game->strt_img, game->color, game->x, game->y, 20);
	mlx_put_image_to_window(game->mlx_init, game->window, game->img, 0, 0);	

}

int main()
{
	void	*wnd;
	void	*mlx;
	void	*img;
	char	*start_img;
	t_game game;

	mlx = mlx_init();
	wnd = mlx_new_window(mlx, 100, 100, "hello world");
	img = mlx_new_image (mlx, 100, 100);
	game.strt_img = mlx_get_data_addr(img, &game.bppx, &game.len_of_line, &game.endian);;
	game.color = 0xf0901e80;
	game.window = wnd;
	game.img = img;
	game.mlx_init = mlx;
	game.x = 0;
	game.y = 0;
	printf("%X\n", game.color);
	print_cub(game.strt_img, game.color, game.x, game.y, 20);
	mlx_put_image_to_window (mlx, wnd, img, game.y, game.x);

	mlx_key_hook(wnd, key_win, &game);
	mlx_mouse_hook(wnd, mouse_win, &game);

	mlx_loop(mlx);
	return(0);
}
