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
	float		oldDirX = game->player.dir[0];
	float		oldDirY = game->player.dir[1];
	float		oldDirX_3D = game->player.dir3D.x;
	float		oldDirY_3D = game->player.dir3D.y;
	//float		oldDirZ_3D = game->player.dir3D.z;
	t_point3D	*p1;
	t_point3D	*p2;
	//int			coll;
	if (game->key.w)
	{
		game->player.pos[0] += round(oldDirX * SPEED);
		game->player.pos[1] += round(oldDirY * SPEED);
	}
	else if (game->key.s)
	{
		game->player.pos[0] -= round(oldDirX * SPEED);
		game->player.pos[1] -= round(oldDirY * SPEED);
	}
	if (game->key.a)
	{
		game->player.pos[0] += round(oldDirY * SPEED);
		game->player.pos[1] -= round(oldDirX * SPEED);
	}
	else if (game->key.d)
	{
		game->player.pos[0] -= round(oldDirY * SPEED);
		game->player.pos[1] += round(oldDirX * SPEED);
	}
	if (game->key.left)
	{
		game->player.dir[0] = oldDirX * cos(-ROT_SPEED) - oldDirY * sin(-ROT_SPEED);
		game->player.dir[1] = oldDirX * sin(-ROT_SPEED) + oldDirY * cos(-ROT_SPEED);
		game->player.dir3D.x = oldDirX_3D * cos(-ROT_SPEED) - oldDirY_3D * sin(-ROT_SPEED);
		game->player.dir3D.y = oldDirX_3D * sin(-ROT_SPEED) + oldDirY_3D * cos(-ROT_SPEED);
		if (game->player.dir[0] > 0)
			game->player.dir3D.angle = atan(game->player.dir[1] / game->player.dir[0]);
		else if (game->player.dir[0] < 0)
			game->player.dir3D.angle = atan(game->player.dir[1] / game->player.dir[0]) + M_PI;
		else
			game->player.dir3D.angle = ((game->player.dir[1] > 0) * 2 - 1) * M_PI / 2;
	}
	else if (game->key.right)
	{
		game->player.dir[0] = oldDirX * cos(ROT_SPEED) - oldDirY * sin(ROT_SPEED);
		game->player.dir[1] = oldDirX * sin(ROT_SPEED) + oldDirY * cos(ROT_SPEED);
		game->player.dir3D.x = oldDirX_3D * cos(ROT_SPEED) - oldDirY_3D * sin(ROT_SPEED);
		game->player.dir3D.y = oldDirX_3D * sin(ROT_SPEED) + oldDirY_3D * cos(ROT_SPEED);
		if (game->player.dir[0] > 0)
			game->player.dir3D.angle = atan(game->player.dir[1] / game->player.dir[0]);
		else if (game->player.dir[0] < 0)
			game->player.dir3D.angle = atan(game->player.dir[1] / game->player.dir[0]) + M_PI;
		else
			game->player.dir3D.angle = ((game->player.dir[1] > 0) * 2 - 1) * M_PI / 2;
	}
	if (game->key.up && game->player.dir3D.z < 0.85)
	{
		p1 = ro_on_z_to_xz(game->player.dir3D);
		p2 = ro_on_y(*p1, ROT_SPEED);
		free(p1);
		p1 = ro_back_on_z(*p2);
		free(p2);
		game->player.dir3D.x = p1->x;
		game->player.dir3D.y = p1->y;
		game->player.dir3D.z = p1->z;
		free(p1);
	}
	else if (game->key.down && game->player.dir3D.z > -0.85)
	{
		p1 = ro_on_z_to_xz(game->player.dir3D);
		p2 = ro_on_y(*p1, -ROT_SPEED);
		free(p1);
		p1 = ro_back_on_z(*p2);
		free(p2);
		game->player.dir3D.x = p1->x;
		game->player.dir3D.y = p1->y;
		game->player.dir3D.z = p1->z;
		free(p1);
	}
}
/*
float dis_h;
		float dis_v;
		float temp_x = game->player.dir[1] * game->dis_p_s;
		float temp_y = -game->player.dir[0] * game->dis_p_s;
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
	float	xx, yy, factor;

	if (game->res_rc[3] == 0)
		wall_h = 0;
	else
		wall_h = round(B_SIZE * game->dis_p_s / game->res_rc[2]);
	if (wall_h > WIN_H)
		wall_h = WIN_H;
	wall_row = (WIN_H - wall_h) / 2;
	while (wall_row < (WIN_H + wall_h) / 2)
	{
		if (wall_row == (WIN_H - wall_h) / 2 || wall_row == (WIN_H + wall_h) / 2 - 1)
			((unsigned int *)game->img.addr)[wall_row * WIN_W + col] = 0x00557766;
		else if (game->res_rc == game->res_rc_h)
			((unsigned int *)game->img.addr)[wall_row * WIN_W + col] = 0x00668833;
		else
			((unsigned int *)game->img.addr)[wall_row * WIN_W + col] = 0x00557733;
		wall_row++;
	}
	//x = game->res_rc[0] - game->player.pos[0];
	//y = game->res_rc[1] - game->player.pos[1];
	//xx = x / sqrt(x * x + y * y) * sqrt((WIN_W / 2 - col) * (WIN_W / 2 - col) + game->dis_p_s * game->dis_p_s);
	//yy = y / sqrt(x * x + y * y) * sqrt((WIN_W / 2 - col) * (WIN_W / 2 - col) + game->dis_p_s * game->dis_p_s);
	xx = -game->player.dir[1] * (col - WIN_W / 2) + game->player.dir[0] * game->dis_p_s;
	yy = game->player.dir[0] * (col - WIN_W / 2) + game->player.dir[1] * game->dis_p_s;
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
	float temp_x = game->player.dir[1] * WIN_W / 2;
	float temp_y = -game->player.dir[0] * WIN_W / 2;
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

void	draw_pixel(t_data *game, int col, int row)
{
	if (game->res_rc_3D[4] != 0
	&& game->res_rc_3D[2] >= -32 && game->res_rc_3D[2] <= 32)
	{
		if (game->res_rc_3D == game->res_rc_h_3D)
			((unsigned int *)game->img.addr)[row * WIN_W + col] = 0x00557766;
		else
			((unsigned int *)game->img.addr)[row * WIN_W + col] = 0x00224411;
	}
	else if (game->res_rc_3D[2] < -32)
	{
		float temp_x = game->res_rc_3D[0] - game->player.pos[0];
		float temp_y = game->res_rc_3D[1] - game->player.pos[1];
		game->res_rc_3D[0] = temp_x * -32 / game->res_rc_3D[2] + game->player.pos[0];
		game->res_rc_3D[1] = temp_y * -32 / game->res_rc_3D[2] + game->player.pos[1];
		if (((int)game->res_rc_3D[0]) % (B_SIZE / 4) == 0
		|| ((int)game->res_rc_3D[1]) % (B_SIZE / 4) == 0
		|| ((int)game->res_rc_3D[0]) % (B_SIZE / 4) == (B_SIZE / 4) - 1
		|| ((int)game->res_rc_3D[1]) % (B_SIZE / 4) == (B_SIZE / 4) - 1)
		((unsigned int *)game->img.addr)[row * WIN_W + col] = 0x00FFFFFF;
	}
}

void	draw_walls_3D(t_data *game)
{
	t_point3D *p1, *p2;
	p1 = ro_on_z_to_xz(game->player.dir3D);
	p2 = ro_on_y(*p1, -M_PI / 2);
	free(p1);
	p1 = ro_back_on_z(*p2); // toward down on screen
	free(p2);
	p2 = cross(game->player.dir3D, *p1); // toward right on screen
	int col, row;
	col = 0;
	row = 0;
	float temp_x = -p1->x * WIN_H / 2 - p2->x * WIN_W / 2;
	float temp_y = -p1->y * WIN_H / 2 - p2->y * WIN_W / 2;
	float temp_z = -p1->z * WIN_H / 2 - p2->z * WIN_W / 2;
	while (col < WIN_W)
	{
		row = 0;
		while (row < WIN_H)
		{
			raycast_3D(game, temp_x, temp_y, temp_z);
			draw_pixel(game, col, row);
			temp_x += p1->x;
			temp_y += p1->y;
			temp_z += p1->z;
			row++;
		}
		temp_x -= p1->x * WIN_H;
		temp_y -= p1->y * WIN_H;
		temp_z -= p1->z * WIN_H;
		temp_x += p2->x;
		temp_y += p2->y;
		temp_z += p2->z;
		col++;
	}
	free(p1);
	free(p2);
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
		//printf("dir: %f %f %f\n", game->player.dir3D.x, game->player.dir3D.y, game->player.dir3D.z);
		draw_walls_3D(game);
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.img_ptr, 0, 0);
	}
	return (0);
}
