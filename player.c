#include "cub3d.h"
#define PI 3.14159
#define PI2 3.14159/2
#define PI3 3*3.14159/2
#define DR 0.0174533

float dist(float ax, float ay, float bx, float by)
{
//	printf("%f %f %f %f\n", ax, ay, bx, by);
	return(sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

void print_vertical_line(int x, int y, int length, t_game *game)
{
	int i;

	i = 0;
	int j = 0;
	while(j < 15)
	{
		i = 0;
		while (i < length)
		{
			print_img_pxl(&game->center_img[(x + j) * 4 + (game->len_of_line * (y + i))], game->color);
			i++;
		}
		j++;
	}
}

void drawRays3D(t_game *game, t_game *new_game)
{
	int r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo;
	float disT;

	ra = game->pa - (30 * DR);
	if (ra < 0)
			ra += 2*PI;
	if (ra > 2*PI)
			ra -= 2*PI;
	int luch1[2];
	int luch2[2];
//	ra = game->pa;





	background(new_game, 800, 800, 0);


	for(int r = 0; r < 60; r++)
	{
		dof = 0;
		float py, px;
		py = game->py;
		px = game->px;
		float aTan = -1/tan(ra);
		float dish = 100000, hx = px, hy=py;
		if (ra > PI)
		{
			ry = (game->py/64)*64;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo*aTan;
		}
		if (ra < PI)
		{
			ry = (game->py/64)*64 + 64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo*aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)rx / 64;
			my = (int)ry / 64;
			if (ra > PI)
				my -= 1;
			mp = my*8 + mx;
			if (mp < 64 && mp > -1 && game->map[mp] == 1)
			{
				hx = rx;
				hy = ry;
				dof = 8;
				dish = dist(px, py, hx, hy);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
	/*	game->color = 0xFFFF0000;
		printf("%f\n", ra);
	//	if (ra > PI)
	//		ry += 64;
		luch1[0] = game->px + 4;
		luch1[1] = game->py + 4;
		luch2[0] = rx;
		luch2[1] = ry;
		line(game, luch1, luch2);*/

		float disv = 100000, vx = px, vy=py;
		float nTan = -tan(ra);
		if (ra > PI2 && ra < PI3)
		{
			rx = (game->px/64)*64;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo*nTan;
		}
		if (ra < PI2 || ra > PI3)
		{
			rx = (game->px/64)*64 + 64;
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = -xo*nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			xo = 64;
			yo = 0;
			dof = 8;
		}
		dof = 0;
		while(dof < 8)
		{
			mx = (int)rx / 64;
			my = (int)ry / 64;
			if (ra > PI2 && ra < PI3)		
				mp = my*8 + mx - 1;
			else
				mp = my*8 + mx;
			if (mp < 64 && mp > -1 && game->map[mp] == 1)
			{
				vx = rx;
				vy = ry;
				dof = 8;
				disv = dist(px, py, vx, vy);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (dish > disv)
		{
			rx = vx;
			ry = vy;
			disT = disv;
		}
		if (dish < disv)
		{
			rx = hx;
			ry = hy;
			disT = dish;
		}
		printf("%f\n%f\n", dish, disv);
		game->color = 0x0000FF00;
		luch1[0] = game->px + 4;
		luch1[1] = game->py + 4;
		luch2[0] = rx;
		luch2[1] = ry;
		line(game, luch1, luch2);




		float ca = game->pa - ra;
		if (ca < 0)
			ca += 2*PI;
		if (ca > 2*PI)
			ca -= 2*PI;
		disT = disT*cos(ca);
		float lineH = (800) / disT;
		if (lineH > 800)
			lineH = 800;
		float lineO = 400 - lineH/2;
		//for (int i = 0; i < 8; i++)
		print_vertical_line(15*r, lineO, lineH, new_game);
		ra += DR;
		if (ra < 0)
			ra += 2*PI;
		if (ra > 2*PI)
			ra -= 2*PI;
	}
	mlx_put_image_to_window(game->mlx_init, new_game->window, new_game->img, 0, 0);	
}

void print_polygon(int **plots, t_game  *game, int edge)
{
	int i;

	i = 0;
	while (i < edge - 1)
		line(game, plots[i++], plots[i + 1]);
	line(game, plots[0], plots[i]);
}

void draw_player(t_game *game, int color)
{
	int i;
	int j;
	int luch1[2];
	int luch2[2];
	printf("%i\n%i\n", game->px, game->py);
	i = 0;
	while(i < 8)
	{
		j = 0;
		while(j < 8)
		{
			print_img_pxl(&game->center_img[(game->px + j) * 4 + (game->len_of_line * (game->py + i))], color);
			j++;
		}
		i++;
	}
	luch1[0] = game->px + 4;
	luch1[1] = game->py + 4;
	luch2[0] = game->px + 4 + game->pdx*5;
	luch2[1] = game->py + 4 + game->pdy*5;
	line(game, luch1, luch2);
	drawRays3D(game, game->new_game);
}

void draw_map(int *map, t_game *game, int mapX, int mapY)
{
	int x0, x, y0, y;
	x = y = 0;
	int **face;
	if((face = alloc_2d(4, 2)) == 0)
		return ;
	while (y < mapY)
	{
		while(x < mapX)
		{
			if (map[x + (y * mapX)] == 1)
				game->color = 0xFFFFFFFF;
			else
				game->color = 0xff;
			x0 = 64 * x;
			y0 = 64 * y;
			face[0][0] = x0 + 1;
			face[0][1] = y0 + 1;
			face[1][0] = x0 + 1;
			face[1][1] = y0 + 64 -1;
			face[2][0] = x0 + 64 - 1;
			face[2][1] = y0 + 64 - 1;
			face[3][0] = x0 + 64 - 1;
			face[3][1] = y0 + 1;
			print_polygon(face, game, 4);
			x++;
		}
		x = 0;
		y++;
	}
}



int	key_win(int key, t_game *game)
{	
	printf("Key in Win : %d\n",key);
	if (key == 119)
	{
		game->px += game->pdx;
		game->py += game->pdy;
		
	}
	if (key == 115)
	{
		game->px -= game->pdx;
		game->py -= game->pdy;

	}
	if (key == 97)
	{
		game->pa -= 0.11;
		if (game->pa < 0)
			game->pa += 2*PI;
		game->pdx = cos(game->pa)* 3;
		game->pdy = sin(game->pa)* 3;
	}
	if (key == 100)
	{
		game->pa += 0.11;
		if (game->pa > 2*PI)
			game->pa -= 2*PI;
		game->pdx = cos(game->pa)* 3;
		game->pdy = sin(game->pa)* 3;
	}
	background(game, 800, 800, 0);
	draw_map(game->map, game, 8, 8);
	draw_player(game, 0xFFFF0000);
	drawRays3D(game, game->new_game);
	mlx_put_image_to_window(game->mlx_init, game->window, game->img, 0, 0);	
}

int main()
{
	int		y = 0;
	int 	**face;
	int 	**top;
	int 	**right;
	int 	***figure;
	t_game game;
	t_game new_game;
	unsigned int		color = 0xFFFFFFFF;
	int map[] = {
		1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,
	};
	game.map = map;
	game.mlx_init = mlx_init();
	game.window = mlx_new_window(game.mlx_init, 800, 800, "hello world");
	game.img = mlx_new_image (game.mlx_init, 800, 800);
	game.strt_img = mlx_get_data_addr(game.img, &game.bppx, &game.len_of_line, &game.endian);
//	game.center_img= &game.strt_img[((900 / 2) * (game.bppx / 8)) + ((900 / 2) * game.len_of_line)];
	game.center_img= game.strt_img;
	game.color = color;
	game.edge = 6;
	game.px = 65;
	game.py = 65;
	game.pa = 0;
	
//	printf("%i\n", plots[0][0]);
//	rotate_triangle(plots, DEG_TO_RAD(270));
//	background(&game, 200, 200, 0x01FF0000);
	new_game.window = mlx_new_window(game.mlx_init, 800, 800, "hello world");
	new_game.img = mlx_new_image(game.mlx_init, 800, 800);
	new_game.strt_img = mlx_get_data_addr(new_game.img, &new_game.bppx, &new_game.len_of_line, &new_game.endian);
	new_game.center_img= new_game.strt_img;
	game.new_game = &new_game;
	new_game.color = 0xFFFF0000;
	draw_map(map, &game, 8, 8);
	draw_player(&game, 0xFFFF0000);
	drawRays3D(&game, &new_game);

	mlx_put_image_to_window (game.mlx_init, game.window, game.img, 0, 0);
	mlx_put_image_to_window (game.mlx_init, new_game.window, new_game.img, 0, 0);
	mlx_key_hook(game.window, key_win, &game);
//	mlx_mouse_hook(game.window, mouse_win, &game);
//	rotate_triangle(plots, DEG_TO_RAD(10));
//	print_triangle(game.strt_img, plots, 0x01FF0000);
	mlx_loop(game.mlx_init);
}