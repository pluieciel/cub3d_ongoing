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
int	collision(t_data *game, float dir_x, float dir_y)
{
	raycast(game, dir_x, dir_y);
	if (game->res_rc_h[2] < COLL_DIS)
		return (1);
	else if (game->res_rc_v[2] < COLL_DIS)
		return (2);
	else
		return (0);
}

void	move_player(t_data *game)
{
	float	oldDirX = game->player.dir[0];
	float	oldDirY = game->player.dir[1];
	int		coll;
	if (game->key.w)
	{
		coll = collision(game, 0, 0);
		game->player.pos[0] += round(oldDirX * 5) * (coll != 2);
		game->player.pos[1] += round(oldDirY * 5) * (coll != 1);
	}
	else if (game->key.s)
	{
		coll = collision(game, -game->player.dir[0] * DIS_P_S * 2, -game->player.dir[1] * DIS_P_S * 2);
		game->player.pos[0] -= round(oldDirX * 5) * (coll != 2);
		game->player.pos[1] -= round(oldDirY * 5) * (coll != 1);
	}
	if (game->key.a)
	{
		coll = collision(game, (-game->player.dir[0] + game->player.dir[1]) * DIS_P_S, (-game->player.dir[1] - game->player.dir[0]) * DIS_P_S);
		game->player.pos[0] += round(oldDirY * 5) * (coll != 2);
		game->player.pos[1] -= round(oldDirX * 5) * (coll != 1);
	}
	else if (game->key.d)
	{
		coll = collision(game, (-game->player.dir[0] - game->player.dir[1]) * DIS_P_S, (-game->player.dir[1] + game->player.dir[0]) * DIS_P_S);
		game->player.pos[0] -= round(oldDirY * 5) * (coll != 2);
		game->player.pos[1] += round(oldDirX * 5) * (coll != 1);
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
	int		wall_h, wall_row, temp_x, temp_y;
	float	x, y, xx, yy, factor;

	if (game->res_rc[3] == 0)
		wall_h = 0;
	else
		wall_h = round(B_SIZE * (WIN_W / 2) / game->res_rc[2]);
	if (wall_h > WIN_H)
		wall_h = WIN_H;
	wall_row = (WIN_H - wall_h) / 2;
	while (wall_row < (WIN_H + wall_h) / 2)
	{
		if (wall_row == (WIN_H - wall_h) / 2 || wall_row == (WIN_H + wall_h) / 2 - 1)
			((unsigned int *)game->img.addr)[wall_row * WIN_W + col] = 0x00557766;
		wall_row++;
	}
	x = game->res_rc[0] - game->player.pos[0];
	y = game->res_rc[1] - game->player.pos[1];
	xx = x / sqrt(x * x + y * y) * sqrt(col * col + 640 * 640);
	yy = y / sqrt(x * x + y * y) * sqrt(col * col + 640 * 640);
	while (wall_row < WIN_H)
	{
		factor = (B_SIZE / 2.0) / (wall_row - WIN_H / 2);
		temp_x = round(xx * factor + game->player.pos[0]);
		temp_y = round(yy * factor + game->player.pos[1]);
		if (temp_x % B_SIZE == 0 || temp_y % B_SIZE == 0 || temp_x % B_SIZE == (B_SIZE - 1) || temp_y % B_SIZE == (B_SIZE - 1))
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
		raycast(game, temp_x, temp_y);
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
