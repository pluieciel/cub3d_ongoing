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

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void	draw_map1(t_data *game)
{
	int	x;
	int	y;
	int i;
	int j;

	((unsigned int *)game->img.addr)[MM_POS_Y * WIN_W + MM_POS_X] = 0x00FFFF00;
	((unsigned int *)game->img.addr)[(MM_POS_Y + (int)round(game->player.dir[1] * 10)) * WIN_W + MM_POS_X + (int)round(game->player.dir[0] * 10)] = 0x00FFFF00;
	y = game->player.pos[1] / B_SIZE - 8;
	while (y <= game->player.pos[1] / B_SIZE + 8)
	{
		x = game->player.pos[0] / B_SIZE - 8;
		while (x < game->player.pos[0] / B_SIZE + 8)
		{
			if (x >= 0 && y >= 0 && x < game->map_w && y < game->map_h && game->map[y][x] == 1)
			{
				i = y * B_SIZE / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR + 1;
				while (i < y * B_SIZE / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR + B_SIZE / MM_FACTOR - 1)
				{
					j = x * B_SIZE / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR + 1;
					while (j < x * B_SIZE / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR + B_SIZE / MM_FACTOR - 1)
					{
						if (i >= 0 && j >= 0 && i < WIN_H && j < WIN_W)//(distance(i, j, MM_POS_Y, MM_POS_X) < 200)//
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

	((unsigned int *)game->img.addr)[MM_POS_Y * WIN_W + MM_POS_X] = 0x00FFFF00;
	//((unsigned int *)game->img.addr)[(MM_POS_Y + (int)round(game->player.dir[1] / 6)) * WIN_W + MM_POS_X + (int)round(game->player.dir[0] / 6)] = 0x00FFFF00;
	y = game->player.pos[1] / B_SIZE - MM_RANGE;
	while (y <= game->player.pos[1] / B_SIZE + MM_RANGE)
	{
		x = game->player.pos[0] / B_SIZE - MM_RANGE;
		while (x < game->player.pos[0] / B_SIZE + MM_RANGE)
		{
			if (x >= 0 && y >= 0 && x < game->map_w && y < game->map_h && game->map[y][x] == 1)
			{
				i = y * B_SIZE / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR + 1;
				while (i < y * B_SIZE / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR + B_SIZE / MM_FACTOR - 1)
				{
					j = x * B_SIZE / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR + 1;
					while (j < x * B_SIZE / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR + B_SIZE / MM_FACTOR - 1)
					{
						if (distance(i, j, MM_POS_Y, MM_POS_X) < 100)
						{
							newj = round(-(j - MM_POS_X) * game->player.dir[1] + (i - MM_POS_Y) * game->player.dir[0]) + MM_POS_X;
							newi = round((j - MM_POS_X) * -game->player.dir[0] - (i - MM_POS_Y) * game->player.dir[1]) + MM_POS_Y;
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
//not good, cannot handle corners
int	no_collision(int dir, t_data *game, int pn)
{
	if (dir == 0)
	{
		if (game->map[game->player.pos[1] / B_SIZE][(game->player.pos[0] + pn * 20) / B_SIZE] == 1)
			return (0);
	}
	else if (dir == 1)
	{
		if (game->map[(game->player.pos[1] + pn * 20) / B_SIZE][game->player.pos[0] / B_SIZE] == 1)
			return (0);
	}
	return (1);
}

void	move_player(t_data *game)
{
	float oldDirX = game->player.dir[0];
	float oldDirY = game->player.dir[1];
	if (game->key.w)
	{
		game->player.pos[0] += round(oldDirX * 5);
		game->player.pos[1] += round(oldDirY * 5);
	}
	else if (game->key.s)
	{
		game->player.pos[0] -= round(oldDirX * 5);
		game->player.pos[1] -= round(oldDirY * 5);
	}
	if (game->key.a)
	{
		game->player.pos[0] += round(oldDirY * 5);
		game->player.pos[1] -= round(oldDirX * 5);
	}
	else if (game->key.d)
	{
		game->player.pos[0] -= round(oldDirY * 5);
		game->player.pos[1] += round(oldDirX * 5);
	}
	if (game->key.left)
	{
		game->player.dir[0] = oldDirX * cos(-ROT_SPEED) - oldDirY * sin(-ROT_SPEED);
		game->player.dir[1] = oldDirX * sin(-ROT_SPEED) + oldDirY * cos(-ROT_SPEED);
	}
	else if (game->key.right)
	{
		game->player.dir[0] = oldDirX * cos(ROT_SPEED) - oldDirY * sin(ROT_SPEED);
		game->player.dir[1] = oldDirX * sin(ROT_SPEED) + oldDirY * cos(ROT_SPEED);
	}
}

int	render(t_data *game)
{
	long long	now;
	long long	diff_millisecs;
	float dis_h;
	float dis_v;

	now = millitimestamp();
	diff_millisecs = now - game->time;
	if (game->win_ptr != NULL && diff_millisecs > 1000 / FPS)
	{
		game->time = now;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		clear_img(&game->img);
		//(((unsigned int *)game->img.addr)[y * WIN_W + x]) = color;
		move_player(game);
		draw_map1(game);
		dis_h = raycast_h(game, 0, 0);
		dis_v = raycast_v(game, 0, 0);
		t_point a;
		t_point b;

		a.x = MM_POS_X;
		a.y = MM_POS_Y;
		a.color = 0xFF0000;
		b.color = 0xFF0000;
		b.x = game->res_rc_h[0] / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR;
		b.y = game->res_rc_h[1] / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR;
		if (dis_h > 0 && dis_h < RAYCAST_RANGE * B_SIZE)
			ft_bresenham(a, b, &game->img);
		b.x = game->res_rc_v[0] / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR;
		b.y = game->res_rc_v[1] / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR;
		a.color = 0x00FF00;
		b.color = 0x00FF00;
		if (dis_v > 0 && dis_v < RAYCAST_RANGE * B_SIZE)
			ft_bresenham(a, b, &game->img);
		int y = (game->res_rc_h[1] / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR);
		int x = (game->res_rc_h[0] / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR);
		if (dis_h > 0 && dis_h < RAYCAST_RANGE * B_SIZE && 0<=y && y<WIN_H && 0<=x && x<WIN_W)
			((unsigned int *)game->img.addr)[y * WIN_W + x] = 0xFFFFFF;
		y = (game->res_rc_v[1] / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR);
		x = (game->res_rc_v[0] / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR);
		if (dis_v > 0 && dis_v < RAYCAST_RANGE * B_SIZE && 0<=y && y<WIN_H && 0<=x && x<WIN_W)
			((unsigned int *)game->img.addr)[y * WIN_W + x] = 0xFFFFFF;
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.img_ptr, 0, 0);
	}
	return (0);
}
