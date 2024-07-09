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
	//((unsigned int *)game->img.addr)[(MM_POS_Y + (int)round(game->player.dir[1] * 10)) * WIN_W + MM_POS_X + (int)round(game->player.dir[0] * 10)] = 0x00FFFF00;
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
	unsigned int	t;
	float	angle;

	//((unsigned int *)game->img.addr)[MM_POS_Y * WIN_W + MM_POS_X] = 0x00FFFF00; //player pos
	angle = atan(1.0 * (WIN_W / 2) / game->dis_p_s);
	i = MM_POS_X - MM_RADIUS;
	while (i <= MM_POS_X + MM_RADIUS)
	{
		j = MM_POS_Y - MM_RADIUS;
		while (j <= MM_POS_Y + MM_RADIUS)
		{
			if (distance(i, j, MM_POS_X, MM_POS_Y) < MM_RADIUS)
			{
				t = ((unsigned int *)game->img.addr)[j * WIN_W + i];
				if (MM_POS_Y > j && atan(1.0 * abs(i - MM_POS_X) / (MM_POS_Y - j)) < angle)
					((unsigned int *)game->img.addr)[j * WIN_W + i]
						= ((((((t >> 16) & 0xff) * 2 + 0x11) / 3) & 0xff) << 16)
						+ ((((((t >> 8) & 0xff) * 2 + 0xff) / 3) & 0xff) << 8)
						+ (((((t) & 0xff) * 2 + 0x11) / 3) & 0xff);
				else
					((unsigned int *)game->img.addr)[j * WIN_W + i]
						= ((((((t >> 16) & 0xff) * 2 + 0xff) / 3) & 0xff) << 16)
						+ ((((((t >> 8) & 0xff) * 2 + 0xff) / 3) & 0xff) << 8)
						+ (((((t) & 0xff) * 2 + 0xff) / 3) & 0xff);
			}
			j++;
		}
		i++;
	}
	
	y = game->player.pos[1] / B_SIZE - MM_RANGE;
	while (y <= game->player.pos[1] / B_SIZE + MM_RANGE)
	{
		x = game->player.pos[0] / B_SIZE - MM_RANGE;
		while (x < game->player.pos[0] / B_SIZE + MM_RANGE)
		{
			if (x >= 0 && y >= 0 && x < game->map_w && y < game->map_h && game->map[y][x] >= 1)
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
							t = ((unsigned int *)game->img.addr)[newi * WIN_W + newj];
							if (game->map[y][x] == 1)
								((unsigned int *)game->img.addr)[newi * WIN_W + newj]
								= ((((((t >> 16) & 0xff) + 0xaa) / 2) & 0xff) << 16)
									+ ((((((t >> 8) & 0xff) + 0xaa) / 2) & 0xff) << 8)
									+ (((((t) & 0xff) + 0xff) / 2) & 0xff);
							else if (game->map[y][x] == 3)
								((unsigned int *)game->img.addr)[newi * WIN_W + newj]
								= ((((((t >> 16) & 0xff) + 0xaa) / 2) & 0xff) << 16)
									+ ((((((t >> 8) & 0xff) + 0xff) / 2) & 0xff) << 8)
									+ (((((t) & 0xff) + 0xaa) / 2) & 0xff);
							else if (game->map[y][x] >= 2)
								((unsigned int *)game->img.addr)[newi * WIN_W + newj]
								= ((((((t >> 16) & 0xff) + 0xff) / 2) & 0xff) << 16)
									+ ((((((t >> 8) & 0xff) + 0xaa) / 2) & 0xff) << 8)
									+ (((((t) & 0xff) + 0xaa) / 2) & 0xff);
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
void	collision(t_data *game, float dir_x, float dir_y, int coll_dis, int type)
{
	raycast(game, dir_x, dir_y, type);
	t_point a;
	t_point b;

	a.x = MM_POS_X;
	a.y = MM_POS_Y;
	a.color = 0xFF0000;
	b.x = game->res_rc_h[0] / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR;
	b.y = game->res_rc_h[1] / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR;
	if (game->res_rc_h[2] > 0 && game->res_rc_h[2] < RAYCAST_RANGE * B_SIZE)
		ft_bresenham(a, b, &game->img);
	a.color = 0x00FF00;
	b.x = game->res_rc_v[0] / MM_FACTOR + MM_POS_X - game->player.pos[0] / MM_FACTOR;
	b.y = game->res_rc_v[1] / MM_FACTOR + MM_POS_Y - game->player.pos[1] / MM_FACTOR;
	if (game->res_rc_v[2] > 0 && game->res_rc_v[2] < RAYCAST_RANGE * B_SIZE)
		ft_bresenham(a, b, &game->img);
	if (game->res_rc_h[2] < coll_dis)
		game->coll_h = 1;
	else if (game->res_rc_v[2] < coll_dis)
		game->coll_v = 1;
}

void	move_player(t_data *game)
{
	float		oldDirX = game->player.dir[0];
	float		oldDirY = game->player.dir[1];
	float		oldDirX_3D = game->player.dir3D.x;
	float		oldDirY_3D = game->player.dir3D.y;
	//float		oldDirZ_3D = game->player.dir3D.z;
	game->coll_h = 0;
	game->coll_v = 0;
	t_point3D	*p1;
	t_point3D	*p2;
	//int			coll;
	if (game->key.w)
	{
		collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS, 0);
		collision(game, game->player.dir[1], -game->player.dir[0], COLL_DIS, 0);
		collision(game, -game->player.dir[1], game->player.dir[0], COLL_DIS, 0);
		collision(game, (sqrt(2)/2) * (game->player.dir[0] - game->player.dir[1]), (sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), COLL_DIS, 0);
		collision(game, (sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), (sqrt(2)/2) * (-game->player.dir[0] + game->player.dir[1]), COLL_DIS, 0);

		if (!game->coll_v)
    		game->player.pos[0] += round(oldDirX * SPEED);
    	if (!game->coll_h)
    	    game->player.pos[1] += round(oldDirY * SPEED);
	}
	else if (game->key.s)
	{
		collision(game, -game->player.dir[0], -game->player.dir[1], COLL_DIS, 0);
		collision(game, game->player.dir[1], -game->player.dir[0], COLL_DIS, 0);
		collision(game, -game->player.dir[1], game->player.dir[0], COLL_DIS, 0);
		collision(game, -(sqrt(2)/2) * (game->player.dir[0] - game->player.dir[1]), -(sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), COLL_DIS, 0);
		collision(game, -(sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), -(sqrt(2)/2) * (-game->player.dir[0] + game->player.dir[1]), COLL_DIS, 0);

		if (!game->coll_v)
    		game->player.pos[0] -= round(oldDirX * SPEED);
    	if (!game->coll_h)
    	    game->player.pos[1] -= round(oldDirY * SPEED);
	}
	if (game->key.a)
	{
		collision(game, game->player.dir[1], -game->player.dir[0], COLL_DIS, 0);
		collision(game, -game->player.dir[0], -game->player.dir[1], COLL_DIS, 0);
		collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS, 0);
		collision(game, (sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), (sqrt(2)/2) * (-game->player.dir[0] + game->player.dir[1]), COLL_DIS, 0);
		collision(game, -(sqrt(2)/2) * (game->player.dir[0] - game->player.dir[1]), -(sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), COLL_DIS, 0);
		
		if (!game->coll_v)
    		game->player.pos[0] += round(oldDirY * SPEED);
    	if (!game->coll_h)
    	    game->player.pos[1] -= round(oldDirX * SPEED);
	}
	else if (game->key.d)
	{
		collision(game, -game->player.dir[1], game->player.dir[0], COLL_DIS, 0);
		collision(game, -game->player.dir[0], -game->player.dir[1], COLL_DIS, 0);
		collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS, 0);
		collision(game, -(sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), -(sqrt(2)/2) * (-game->player.dir[0] + game->player.dir[1]), COLL_DIS, 0);
		collision(game, (sqrt(2)/2) * (game->player.dir[0] - game->player.dir[1]), (sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), COLL_DIS, 0);

		if (!game->coll_v)
    		game->player.pos[0] -= round(oldDirY * SPEED);
    	if (!game->coll_h)
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
	if (game->key.up && game->player.dir3D.z < 0.95)
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
	else if (game->key.down && game->player.dir3D.z > -0.95)
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
		raycast(game, temp_x + game->player.dir[0] * game->dis_p_s, temp_y + game->player.dir[1] * game->dis_p_s, 0);
		draw_line(game, col);
		temp_x -= game->player.dir[1];
		temp_y += game->player.dir[0];
		col++;
	}
}

void	do_doors_h(t_data *game, int col, int row)
{
	float	r;
	float	c;
	unsigned int	t;
	float	shadow;
	float	offset;

	if (game->doors_h[game->num_doors_h][3] < game->nearest_wall_dis)
	{
		shadow = 1.0 - (fmin(game->doors_h[game->num_doors_h][3], 8 * B_SIZE) / (8 * B_SIZE));
		if (game->doors_h[game->num_doors_h][4] == 1)
			c = round(fmod(game->doors_h[game->num_doors_h][0], B_SIZE) / B_SIZE * game->img_door.w);
		else
			c = round((1 - fmod(game->doors_h[game->num_doors_h][0], B_SIZE) / B_SIZE) * game->img_door.w);
		r = round((1 - fmod(game->doors_h[game->num_doors_h][2] + 32, B_SIZE) / B_SIZE) * game->img_door.h);
		offset = (game->map[(int)game->doors_h[game->num_doors_h][6]][(int)game->doors_h[game->num_doors_h][5]] - 2) * game->img_door.w;
		if ((int)c < game->img_door.w / 2 && (int)c + (int)offset < game->img_door.w / 2)
		{
			t = ((unsigned int *)game->img_door.addr)[(int)r * game->img_door.w + (int)c + (int)offset];
			if (t != 4278190080)
				((unsigned int *)game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
		else if ((int)c > game->img_door.w / 2 && (int)c - (int)offset > game->img_door.w / 2)
		{
			t = ((unsigned int *)game->img_door.addr)[(int)r * game->img_door.w + (int)c - (int)offset];
			if (t != 4278190080)
				((unsigned int *)game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
	}
	game->num_doors_h--;
}

void	do_doors_v(t_data *game, int col, int row)
{
	float	r;
	float	c;
	unsigned int	t;
	float	shadow;
	float	offset;

	if (game->doors_v[game->num_doors_v][3] < game->nearest_wall_dis)
	{
		shadow = 1.0 - (fmin(game->doors_v[game->num_doors_v][3], 8 * B_SIZE) / (8 * B_SIZE));
		if (game->doors_v[game->num_doors_v][4] == 1)
			c = round(fmod(game->doors_v[game->num_doors_v][1], B_SIZE) / B_SIZE * game->img_door.w);
		else
			c = round((1 - fmod(game->doors_v[game->num_doors_v][1], B_SIZE) / B_SIZE) * game->img_door.w);
		r = round((1 - fmod(game->doors_v[game->num_doors_v][2] + 32, B_SIZE) / B_SIZE) * game->img_door.h);
		offset = (game->map[(int)game->doors_v[game->num_doors_v][6]][(int)game->doors_v[game->num_doors_v][5]] - 2) * game->img_door.w;
		if ((int)c < game->img_door.w / 2 && (int)c + (int)offset < game->img_door.w / 2)
		{
			t = ((unsigned int *)game->img_door.addr)[(int)r * game->img_door.w + (int)c + (int)offset];
			if (t != 4278190080)
				((unsigned int *)game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
		else if ((int)c > game->img_door.w / 2 && (int)c - (int)offset > game->img_door.w / 2)
		{
			t = ((unsigned int *)game->img_door.addr)[(int)r * game->img_door.w + (int)c - (int)offset];
			if (t != 4278190080)
				((unsigned int *)game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
	}
	game->num_doors_v--;
}

void	draw_pixel(t_data *game, int col, int row)
{
	float	temp_x;
	float	temp_y;
	float	r;
	float	c;
	float	shadow;
	unsigned int	t;

	game->nearest_wall_dis = RAYCAST_RANGE * B_SIZE;
	if (game->res_rc_3D[4] != 0
	&& game->res_rc_3D[2] >= -32 && game->res_rc_3D[2] <= 32)
	{
		shadow = 1.0 - (fmin(game->res_rc_3D[3], 8 * B_SIZE) / (8 * B_SIZE));
		if (game->res_rc_3D == game->res_rc_h_3D)
		{
			if (game->res_rc_3D[4] == 1)
				c = round(fmod(game->res_rc_3D[0], B_SIZE) / B_SIZE * game->img_wall.w);
			else
				c = round((1 - fmod(game->res_rc_3D[0], B_SIZE) / B_SIZE) * game->img_wall.w);
			r = round((1 - fmod(game->res_rc_3D[2] + 32, B_SIZE) / B_SIZE) * game->img_wall.h);
			t = ((unsigned int *)game->img_wall.addr)[(int)r * game->img_wall.w + (int)c];
			((unsigned int *)game->img.addr)[row * WIN_W + col]
			= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
				+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
				+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
		else
		{
			if (game->res_rc_3D[4] == 1)
				c = round(fmod(game->res_rc_3D[1], B_SIZE) / B_SIZE * game->img_wall.w);
			else
				c = round((1 - fmod(game->res_rc_3D[1], B_SIZE) / B_SIZE) * game->img_wall.w);
			r = round((1 - fmod(game->res_rc_3D[2] + 32, B_SIZE) / B_SIZE) * game->img_wall.h);
			t = ((unsigned int *)game->img_wall.addr)[(int)r * game->img_wall.w + (int)c];
			((unsigned int *)game->img.addr)[row * WIN_W + col]
			= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
				+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
				+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
		game->nearest_wall_dis = game->res_rc_3D[3];
	}
	else if (game->res_rc_3D[2] < -32)
	{
		temp_x = game->res_rc_3D[0] - game->player.pos[0];
		temp_y = game->res_rc_3D[1] - game->player.pos[1];
		game->res_rc_3D[0] = temp_x * -32 / game->res_rc_3D[2] + game->player.pos[0];
		game->res_rc_3D[1] = temp_y * -32 / game->res_rc_3D[2] + game->player.pos[1];
		c = fmod(game->res_rc_3D[0], B_SIZE) / B_SIZE;
		c += (c < 0);
		c = round((1 - c) * game->img_floor.w);
		r = fmod(game->res_rc_3D[1], B_SIZE) / B_SIZE;
		r += (r < 0);
		r = round((1 - r) * game->img_floor.h);
		game->res_rc_3D[3] = distance(game->res_rc_3D[0], game->res_rc_3D[1], game->player.pos[0], game->player.pos[1]);
		shadow = 1.0 - (fmin(game->res_rc_3D[3], 8 * B_SIZE) / (8 * B_SIZE));
		t = ((unsigned int *)game->img_floor.addr)[(int)r * game->img_floor.w + (int)c];
		((unsigned int *)game->img.addr)[row * WIN_W + col]
		= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
			+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
			+ ((int)round(((t) & 0xff) * shadow) & 0xff);
	}
	else if (game->res_rc_3D[2] >= 0)
	{
		temp_x = game->res_rc_3D[0] - game->player.pos[0];
		temp_y = game->res_rc_3D[1] - game->player.pos[1];
		r = game->res_rc_3D[2] / sqrt(temp_x * temp_x + temp_y * temp_y + game->res_rc_3D[2] * game->res_rc_3D[2]);
		r = fmin(1.0, r);
		r = 1.0 - asin(r) / (M_PI / 2);
		if (temp_x != 0)
			c = (atan(temp_y / temp_x) + M_PI * (temp_x < 0) + (M_PI / 2)) / (M_PI * 2);
		else
			c = 1.0 / 4 + 1.0 / 2 * (temp_y < 0);
		r *= game->img_sky.h;
		c *= game->img_sky.w;
		((unsigned int *)game->img.addr)[row * WIN_W + col] = ((unsigned int *)game->img_sky.addr)[((int)round(r)) * game->img_sky.w + (int)round(c)];
	}
	while (game->num_doors_h >= 0 || game->num_doors_v >= 0)
	{
		if (game->num_doors_h < 0)
			do_doors_v(game, col, row);
		else if (game->num_doors_v < 0)
			do_doors_h(game, col, row);
		else if (game->doors_h[game->num_doors_h][3] < game->doors_v[game->num_doors_v][3])
			do_doors_v(game, col, row);
		else
			do_doors_h(game, col, row);
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

/*int	find_door(t_data *game, int x, int y)
{
	t_door	*temp;

	temp = game->doors;
	while (temp)
	{
		if (temp->x == x && temp->y == y)
			return (1);
	}
	return (0);
}*/

void	move_doors(t_data *game)
{
	t_door	*new;
	t_door	*temp;
	t_door	*prev;

	// add new door into list
	if (game->op_door == 1)
	{
		collision(game, game->player.dir[0], game->player.dir[1], OPEN_DIS, 1);
		if ((game->coll_h || game->coll_v)
		&& (game->map[(int)game->res_rc[5]][(int)game->res_rc[4]] == 2
		|| game->map[(int)game->res_rc[5]][(int)game->res_rc[4]] == 3))
		{
			new = gc_malloc(sizeof(t_door), &game->gc);
			new->next = game->doors;
			new->x = (int)game->res_rc[4];
			new->y = (int)game->res_rc[5];
			new->open_close = (game->map[new->y][new->x] == 3);
			game->doors = new;
		}
	}
	game->op_door = 0;
	// move the doors in list one by one
	temp = game->doors;
	while (temp)
	{
		game->map[temp->y][temp->x] += ((temp->open_close) * (-2) + 1) * 0.1;
		if (game->map[temp->y][temp->x] <= 2)
			game->map[temp->y][temp->x] = 2;
		else if (game->map[temp->y][temp->x] >= 3)
			game->map[temp->y][temp->x] = 3;
		temp = temp->next;
	}
	// remove finished doors from the list
	temp = game->doors;
	prev = NULL;
	while (temp && (game->map[temp->y][temp->x] <= 2
					|| game->map[temp->y][temp->x] >= 3))
	{
		game->doors = temp->next;
		temp = game->doors;
	}
	while (temp)
	{
		while (temp && (game->map[temp->y][temp->x] != 2
						&& game->map[temp->y][temp->x] != 3))
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
			return ;
		prev->next = temp->next;
		temp = prev->next;
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
		//draw_walls(game);
		move_doors(game);
		move_player(game);
		//printf("dir: %f %f %f\n", game->player.dir3D.x, game->player.dir3D.y, game->player.dir3D.z);
		draw_walls_3D(game);
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.img_ptr, 0, 0);
	}
	return (0);
}
