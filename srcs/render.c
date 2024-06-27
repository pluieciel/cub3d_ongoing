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

void	draw_minimap(t_data *game)
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
						if (distance(i, j, MM_POS_Y, MM_POS_X) < MM_RADIUS)
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
/*
float dis_h;
		float dis_v;
		float temp_x = game->player.dir[1] * DIS_P_S;
		float temp_y = -game->player.dir[0] * DIS_P_S;
		int i;

		i = 0;
		while (i < WIN_W)
		{
			dis_h = game->res_rc_h[2] = raycast_h(game, temp_x, temp_y);
			dis_v = game->res_rc_v[2] = raycast_v(game, temp_x, temp_y);
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
			temp_x -= game->player.dir[1];
			temp_y += game->player.dir[0];
			i++;
			}*/

void	draw_line(t_data *game, int col)
{
	float	x;
	float	y;
	float	dis;
	float	dir;
	int		color;

	if (game->res_rc_h[2] < game->res_rc_v[2])
	{
		x = game->res_rc_h[0];
		y = game->res_rc_h[1];
		dis = game->res_rc_h[2];
		dir = game->res_rc_h[3];
		color = 0x00556622;
	}
	else
	{
		x = game->res_rc_v[0];
		y = game->res_rc_v[1];
		dis = game->res_rc_v[2];
		dir = game->res_rc_v[3];
		color = 0x00113322;
	}
	if (dir == 0)
		return ;
	float wall_h = WIN_W / 2 / (dis / B_SIZE);
	if (wall_h > WIN_H)
		wall_h = WIN_H;
	int wall_row = (WIN_H - wall_h) / 2;
	while (wall_row < (WIN_H + wall_h) / 2)
	{
		((unsigned int *)game->img.addr)[wall_row * WIN_W + col] = color;
		wall_row++;
	}
	while (wall_row < WIN_H)
	{
		float factor = (B_SIZE / 2.0) / (wall_row - WIN_H / 2);
		//printf("factor: %f\n", factor);
		float xx = x - game->player.pos[0];
		float yy = y - game->player.pos[1];
		float xxx = xx / sqrt(xx * xx + yy * yy);
		float yyy = yy / sqrt(xx * xx + yy * yy);
		int tempx = round(xxx * sqrt(col * col + 320 * 320 * 3) * factor + game->player.pos[0]);
		int tempy = round(yyy * sqrt(col * col + 320 * 320 * 3) * factor + game->player.pos[1]);
		if (tempx % B_SIZE <= 1 || tempy % B_SIZE <= 1 || tempx % B_SIZE >= (B_SIZE - 1)|| tempy % B_SIZE >= (B_SIZE - 1))
			((unsigned int *)game->img.addr)[wall_row * WIN_W + col] = 0xFFFFFF;
		wall_row++;
	}
}

void	draw_walls(t_data *game)
{
	float temp_x = game->player.dir[1] * DIS_P_S;
	float temp_y = -game->player.dir[0] * DIS_P_S;
	int col;
	col = 0;
	while (col < WIN_W)
	{
		game->res_rc_h[2] = raycast_h(game, temp_x, temp_y);
		game->res_rc_v[2] = raycast_v(game, temp_x, temp_y);
		draw_line(game, col);
		temp_x -= game->player.dir[1];
		temp_y += game->player.dir[0];
		col++;
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
		draw_walls(game);
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.img_ptr, 0, 0);
	}
	return (0);
}
