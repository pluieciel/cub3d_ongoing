#include "cub3D.h"

void	clear_img(t_img1 *img)
{
	int	i;

	i = 0;
	while (i < img->w * img->h)
	{
		((unsigned int *)img->addr)[i] = 0;
		i++;
	}
}

int	distance(int x1, int y1, int x2, int y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void	draw_map1(t_data *game)
{
	int	x;
	int	y;
	int i;
	int j;

	((unsigned int *)game->img.addr)[WIN_H / 2 * WIN_W + WIN_W / 2] = 0x00FFFF00;
	((unsigned int *)game->img.addr)[(WIN_H / 2 + (int)round(game->player.dir[1] / 6)) * WIN_W + WIN_W / 2 + (int)round(game->player.dir[0] / 6)] = 0x00FFFF00;
	y = game->player.pos[1] / 64 - 8;
	while (y <= game->player.pos[1] / 64 + 8)
	{
		x = game->player.pos[0] / 64 - 8;
		while (x < game->player.pos[0] / 64 + 8)
		{
			if (x >= 0 && y >= 0 && x < game->map_w && y < game->map_h && game->map[y][x] == 1)
			{
				i = y * 32 + WIN_H / 2 - game->player.pos[1] / 2 + 1;
				while (i < y * 32 + WIN_H / 2 - game->player.pos[1] / 2 + 32 - 1)
				{
					j = x * 32 + WIN_W / 2 - game->player.pos[0] / 2 + 1;
					while (j < x * 32 + WIN_W / 2 - game->player.pos[0] / 2 + 32 - 1)
					{	
						if (distance(i, j, WIN_H / 2, WIN_W / 2) < 200)//(i >= 0 && j >= 0 && i < WIN_H && j < WIN_W)
							((unsigned int *)game->img.addr)[i * WIN_W + j] = 0x00AAAAFF;
						j++;
					}
					i++;
				}
			}
			x++;
		}
		y++;
	}
}

void	draw_map2(t_data *game)
{
	int	x;
	int	y;
	int i;
	int j;
	int newi;
	int newj;

	((unsigned int *)game->img.addr)[WIN_H / 2 * WIN_W + WIN_W / 2] = 0x00FFFF00;
	//((unsigned int *)game->img.addr)[(WIN_H / 2 + (int)round(game->player.dir[1] / 6)) * WIN_W + WIN_W / 2 + (int)round(game->player.dir[0] / 6)] = 0x00FFFF00;
	y = game->player.pos[1] / 64 - 8;
	while (y <= game->player.pos[1] / 64 + 8)
	{
		x = game->player.pos[0] / 64 - 8;
		while (x < game->player.pos[0] / 64 + 8)
		{
			if (x >= 0 && y >= 0 && x < game->map_w && y < game->map_h && game->map[y][x] == 1)
			{
				i = y * 32 + WIN_H / 2 - game->player.pos[1] / 2 + 1;
				while (i < y * 32 + WIN_H / 2 - game->player.pos[1] / 2 + 32 - 1)
				{
					j = x * 32 + WIN_W / 2 - game->player.pos[0] / 2 + 1;
					while (j < x * 32 + WIN_W / 2 - game->player.pos[0] / 2 + 32 - 1)
					{	
						if (distance(i, j, WIN_H / 2, WIN_W / 2) < 200)
						{
							newj = -round((j - WIN_W / 2) * game->player.dir[1] / 64 - -(i - WIN_H / 2) * -game->player.dir[0] / 64) + WIN_W / 2;
							newi = round((j - WIN_W / 2) * -game->player.dir[0] / 64 + -(i - WIN_H / 2) * game->player.dir[1] / 64) + WIN_H / 2;
							((unsigned int *)game->img.addr)[newi * WIN_W + newj] = 0x00AAAAFF;
						}
						j++;
					}
					i++;
				}
			}
			x++;
		}
		y++;
	}
}

void	move_player(t_data *game)
{
	float oldDirX = game->player.dir[0];
	float oldDirY = game->player.dir[1];
	if (game->key.w)
	{
		game->player.pos[0] += round(oldDirX * 5 / 64);
		game->player.pos[1] += round(oldDirY * 5 / 64);
	}
	else if (game->key.s)
	{
		game->player.pos[0] -= round(oldDirX * 5 / 64);
		game->player.pos[1] -= round(oldDirY * 5 / 64);
	}
	if (game->key.a)
	{
		game->player.pos[0] += round(oldDirY * 5 / 64);
		game->player.pos[1] -= round(oldDirX * 5 / 64);
	}
	else if (game->key.d)
	{
		game->player.pos[0] -= round(oldDirY * 5 / 64);
		game->player.pos[1] += round(oldDirX * 5 / 64);
	}
	if (game->key.left)
	{
		game->player.dir[0] = oldDirX * cos(-0.1) - oldDirY * sin(-0.1);
		game->player.dir[1] = oldDirX * sin(-0.1) + oldDirY * cos(-0.1);
	}
	else if (game->key.right)
	{
		game->player.dir[0] = oldDirX * cos(0.1) - oldDirY * sin(0.1);
		game->player.dir[1] = oldDirX * sin(0.1) + oldDirY * cos(0.1);
	}
}

int	render(t_data *game)
{
	long long	now;
	long long	diff_millisecs;

	now = millitimestamp();
	diff_millisecs = now - game->time;
	if (game->win_ptr != NULL && diff_millisecs > 1000 / FPS)
	{
		game->time = now;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		clear_img(&game->img);
		//(((unsigned int *)game->img.addr)[y * WIN_W + x]) = color;
		move_player(game);
		draw_map2(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.img_ptr, 0, 0);
	}
	return (0);
}
