#include "cub3d.h"

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void	change_image_color(t_data *game, t_image *img)
{
    int i;
    int j;
	unsigned int t;
	t_color target;
	t_color new;
    
    i = 0;
    while (i < img->w)
    {
        j = 0;
        while (j < img->h)
        {
			t = ((unsigned int *)img->addr)[j * img->w + i];
            if (t != TRANSPARENT_COLOR)
			{              
			  	target = int_to_rgb(game->hud_color);
				shade_color(&target, t & 0xFF);
				set_rgb(target.r / 255, target.g / 255, target.b / 255, &new);
                ((unsigned int *)img->addr)[j * img->w + i] = rgb_to_int(new);
			}
			j++;
		}
		i++;
	}
}

void	render_image(t_data *game, t_image *img, int x, int y)
{
	int				i;
	int				j;
	int				dest_x;
	int				dest_y;
	unsigned int	t;

	i = 0;
	while (i < WIN_W && i < img->w)
	{
		j = 0;
		while (j < WIN_H && j < img->h)
		{
			t = ((unsigned int *)img->addr)[j * img->w + i];
			dest_x = i + x;
			dest_y = j + y;
			if (dest_x >= 0 && dest_x < WIN_W && dest_y >= 0 && dest_y < WIN_H
				&& t != TRANSPARENT_COLOR)
				((unsigned int *)game->img.addr)[dest_y * WIN_W + dest_x] = t;
			j++;
		}
		i++;
	}
}
void	draw_block(t_data *game)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		newi;
	int		newj;
	t_color	c;
	t_color	hud_c;
	t_color	c2;

	hud_c = int_to_rgb(game->hud_color);
	i = MM_POS_Y - MM_RADIUS - 1;
	while (++i <= MM_POS_Y + MM_RADIUS)
	{
		j = MM_POS_X - MM_RADIUS - 1;
		while (++j <= MM_POS_X + MM_RADIUS)
		{
			x = ((j - MM_POS_X) * B_SIZE / MM_FACTOR + game->player.x)
				/ B_SIZE;
			y = ((i - MM_POS_Y) * B_SIZE / MM_FACTOR + game->player.y)
				/ B_SIZE;
			if (x >= 0 && y >= 0 && x < game->map_w && y < game->map_h
				&& game->map[y][x] >= 1)
			if (distance(i, j, MM_POS_Y, MM_POS_X) < MM_RADIUS)
			{
				newj = round(-(j - MM_POS_X) * game->player.dir_y
						+ (i - MM_POS_Y) * game->player.dir_x)
					+ MM_POS_X;
				newi = round((j - MM_POS_X) * -game->player.dir_x
						- (i - MM_POS_Y) * game->player.dir_y)
					+ MM_POS_Y;
				c = int_to_rgb(((unsigned int *)game->img.addr)[newi * WIN_W
					+ newj]);
				if (game->map[y][x] == 1)
				{
					mix_color(&c, hud_c, 2, 1);
					shade_color(&c, 0.6);
					((unsigned int *)game->img.addr)[newi * WIN_W
						+ newj] = rgb_to_int(c);
				}
				else if (game->map[y][x] == 3)
				{
					set_rgb(0, 0x80, 0x80, &c2);
					mix_color(&c, c2, 2, 1);
					((unsigned int *)game->img.addr)[newi * WIN_W
						+ newj] = rgb_to_int(c);
				}
				else if (game->map[y][x] >= 2)
				{
					set_rgb(0x80, 0, 0, &c2);
					mix_color(&c, c2, 2, 1);
					((unsigned int *)game->img.addr)[newi * WIN_W
						+ newj] = rgb_to_int(c);
				}
			}
		}
	}
}

void	draw_bg(t_data *game, int i, int j, float angle)
{
	t_color	c;
	t_color	hud_c;

	hud_c = int_to_rgb(game->hud_color);
	if (distance(i, j, MM_POS_X, MM_POS_Y) < MM_RADIUS)
	{
		c = int_to_rgb(((unsigned int *)game->img.addr)[j * WIN_W + i]);
		if (MM_POS_Y > j && atan(1.0 * abs(i - MM_POS_X) / (MM_POS_Y
					- j)) < angle)
			((unsigned int *)game->img.addr)[j * WIN_W
				+ i] = rgb_to_int(*mix_color(&c, hud_c, 1, 1));
		else
			((unsigned int *)game->img.addr)[j * WIN_W
				+ i] = rgb_to_int(*mix_color(&c, hud_c, 2, 1));
	}
}

void	draw_minimap(t_data *game)
{
	int		i;
	int		j;
	float	angle;

	angle = atan(1.0 * (WIN_W / 2) / game->dis_p_s);
	i = MM_POS_X - MM_RADIUS - 1;
	while (++i <= MM_POS_X + MM_RADIUS)
	{
		j = MM_POS_Y - MM_RADIUS - 1;
		while (++j <= MM_POS_Y + MM_RADIUS)
			draw_bg(game, i, j, angle);
	}
	draw_block(game);
}

void	collision(t_data *game, float dir_x, float dir_y, int coll_dis)
{
	raycast(game, dir_x, dir_y, (coll_dis == OPEN_DIS));
	if (game->res_rc_h[2] < coll_dis && game->res_rc_h[2] < game->res_rc_v[2])
	{
		game->coll_h = 1;
		if (coll_dis == OPEN_DIS)
			game->coll_door_h = 1;
	}
	if (game->res_rc_v[2] < coll_dis && game->res_rc_v[2] < game->res_rc_h[2])
	{
		game->coll_v = 1;
		if (coll_dis == OPEN_DIS)
			game->coll_door_v = 1;
	}
}

void	do_jump(t_data *game)
{
	if (game->player.z == 0 && game->player.v_up == 0)
		game->player.v_up = JUMP_VELOCITY;
	else if (game->player.z < 0)
	{
		game->player.v_up = 0;
		game->player.z = 0;
		game->key.space = 0;
	}
	else
	{
		game->player.z += game->player.v_up * game->timestep / 1000;
		game->player.v_up -= GRAVITY * game->timestep / 1000;
	}
}

void	move_player(t_data *game)
{
	float	oldDirX;
	float	oldDirY;
	float	oldDirX_3d;
	float	oldDirY_3d;

	oldDirX = game->player.dir_x;
	oldDirY = game->player.dir_y;
	oldDirX_3d = game->player.dir3d.x;
	oldDirY_3d = game->player.dir3d.y;
	game->coll_h = 0;
	game->coll_v = 0;
	if (game->key.w)
	{
		collision(game, game->player.dir_x, game->player.dir_y, COLL_DIS);
		collision(game, game->player.dir_y, -game->player.dir_x, COLL_DIS);
		collision(game, -game->player.dir_y, game->player.dir_x, COLL_DIS);
		collision(game, (sqrt(2) / 2) * (game->player.dir_x
				- game->player.dir_y), (sqrt(2) / 2) * (game->player.dir_x
				+ game->player.dir_y), COLL_DIS);
		collision(game, (sqrt(2) / 2) * (game->player.dir_x
				+ game->player.dir_y), (sqrt(2) / 2) * (-game->player.dir_x
				+ game->player.dir_y), COLL_DIS);
		if (!game->coll_v)
			game->player.x += round(oldDirX * game->player.speed);
		if (!game->coll_h)
			game->player.y += round(oldDirY * game->player.speed);
	}
	else if (game->key.s)
	{
		collision(game, -game->player.dir_x, -game->player.dir_y, COLL_DIS);
		collision(game, game->player.dir_y, -game->player.dir_x, COLL_DIS);
		collision(game, -game->player.dir_y, game->player.dir_x, COLL_DIS);
		collision(game, -(sqrt(2) / 2) * (game->player.dir_x
				- game->player.dir_y), -(sqrt(2) / 2) * (game->player.dir_x
				+ game->player.dir_y), COLL_DIS);
		collision(game, -(sqrt(2) / 2) * (game->player.dir_x
				+ game->player.dir_y), -(sqrt(2) / 2) * (-game->player.dir_x
				+ game->player.dir_y), COLL_DIS);
		if (!game->coll_v)
			game->player.x -= round(oldDirX * game->player.speed);
		if (!game->coll_h)
			game->player.y -= round(oldDirY * game->player.speed);
	}
	if (game->key.a)
	{
		collision(game, game->player.dir_y, -game->player.dir_x, COLL_DIS);
		collision(game, -game->player.dir_x, -game->player.dir_y, COLL_DIS);
		collision(game, game->player.dir_x, game->player.dir_y, COLL_DIS);
		collision(game, (sqrt(2) / 2) * (game->player.dir_x
				+ game->player.dir_y), (sqrt(2) / 2) * (-game->player.dir_x
				+ game->player.dir_y), COLL_DIS);
		collision(game, -(sqrt(2) / 2) * (game->player.dir_x
				- game->player.dir_y), -(sqrt(2) / 2) * (game->player.dir_x
				+ game->player.dir_y), COLL_DIS);
		if (!game->coll_v)
			game->player.x += round(oldDirY * game->player.speed);
		if (!game->coll_h)
			game->player.y -= round(oldDirX * game->player.speed);
	}
	else if (game->key.d)
	{
		collision(game, -game->player.dir_y, game->player.dir_x, COLL_DIS);
		collision(game, -game->player.dir_x, -game->player.dir_y, COLL_DIS);
		collision(game, game->player.dir_x, game->player.dir_y, COLL_DIS);
		collision(game, -(sqrt(2) / 2) * (game->player.dir_x
				+ game->player.dir_y), -(sqrt(2) / 2) * (-game->player.dir_x
				+ game->player.dir_y), COLL_DIS);
		collision(game, (sqrt(2) / 2) * (game->player.dir_x
				- game->player.dir_y), (sqrt(2) / 2) * (game->player.dir_x
				+ game->player.dir_y), COLL_DIS);
		if (!game->coll_v)
			game->player.x -= round(oldDirY * game->player.speed);
		if (!game->coll_h)
			game->player.y += round(oldDirX * game->player.speed);
	}
	if (game->key.left)
	{
		game->player.dir_x = oldDirX * cos(-ROT_SPEED) - oldDirY
			* sin(-ROT_SPEED);
		game->player.dir_y = oldDirX * sin(-ROT_SPEED) + oldDirY
			* cos(-ROT_SPEED);
		game->player.dir3d.x = oldDirX_3d * cos(-ROT_SPEED) - oldDirY_3d
			* sin(-ROT_SPEED);
		game->player.dir3d.y = oldDirX_3d * sin(-ROT_SPEED) + oldDirY_3d
			* cos(-ROT_SPEED);
		get_vector_right(game, &game->player.v_right);
		get_vector_down(game, &game->player.v_right, &game->player.v_down);
	}
	else if (game->key.right)
	{
		game->player.dir_x = oldDirX * cos(ROT_SPEED) - oldDirY
			* sin(ROT_SPEED);
		game->player.dir_y = oldDirX * sin(ROT_SPEED) + oldDirY
			* cos(ROT_SPEED);
		game->player.dir3d.x = oldDirX_3d * cos(ROT_SPEED) - oldDirY_3d
			* sin(ROT_SPEED);
		game->player.dir3d.y = oldDirX_3d * sin(ROT_SPEED) + oldDirY_3d
			* cos(ROT_SPEED);
		get_vector_right(game, &game->player.v_right);
		get_vector_down(game, &game->player.v_right, &game->player.v_down);
	}
	if (game->key.up && game->player.dir3d.z < 0.95)
	{
		rotate_u(&game->player.dir3d, game->player.dir3d, game->player.v_down,
			-ROT_SPEED);
		get_vector_down(game, &game->player.v_right, &game->player.v_down);
	}
	else if (game->key.down && game->player.dir3d.z > -0.95)
	{
		rotate_u(&game->player.dir3d, game->player.dir3d, game->player.v_down,
			ROT_SPEED);
		get_vector_down(game, &game->player.v_right, &game->player.v_down);
	}
	if (!game->key.space && game->key.ctrl)
		game->player.z = -20;
	else if (!game->key.space && !game->key.ctrl)
		game->player.z = 0;
	if (game->key.shift)
		game->player.speed = SPEED * 2;
	else if (!game->key.shift)
		game->player.speed = SPEED;
	if (game->key.space)
		do_jump(game);
}

void	do_doors_h(t_raycast *ray, int col, int row)
{
	float			r;
	float			c;
	unsigned int	t;
	float			shadow;
	float			offset;

	if (ray->doors_h[ray->num_doors_h][3] < ray->nearest_wall_dis)
	{
		shadow = 1.0 - (fmin(ray->doors_h[ray->num_doors_h][3], 8 * B_SIZE) / (8
					* B_SIZE));
		if (ray->doors_h[ray->num_doors_h][4] == 1)
			c = round(fmod(ray->doors_h[ray->num_doors_h][0], B_SIZE) / B_SIZE
					* ray->g->img_door.w);
		else
			c = round((1 - fmod(ray->doors_h[ray->num_doors_h][0], B_SIZE)
						/ B_SIZE) * ray->g->img_door.w);
		r = round((1 - fmod(ray->doors_h[ray->num_doors_h][2] + 32
						+ ray->g->player.z, B_SIZE) / B_SIZE)
				* ray->g->img_door.h);
		offset = (ray->g->map[(int)ray->doors_h[ray->num_doors_h][6]][(int)ray->doors_h[ray->num_doors_h][5]]
				- 2) * ray->g->img_door.w;
		if ((int)c < ray->g->img_door.w / 2 && (int)c
			+ (int)offset < ray->g->img_door.w / 2)
		{
			t = ((unsigned int *)ray->g->img_door.addr)[(int)r
				* ray->g->img_door.w + (int)c + (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->g->img.addr)[row * WIN_W
					+ col] = (((int)round(((t >> 16) & 0xff)
								* shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t)&0xff) * shadow) & 0xff);
		}
		else if ((int)c > ray->g->img_door.w / 2 && (int)c
			- (int)offset > ray->g->img_door.w / 2)
		{
			t = ((unsigned int *)ray->g->img_door.addr)[(int)r
				* ray->g->img_door.w + (int)c - (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->g->img.addr)[row * WIN_W
					+ col] = (((int)round(((t >> 16) & 0xff)
								* shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t)&0xff) * shadow) & 0xff);
		}
	}
	ray->num_doors_h--;
}

void	do_doors_v(t_raycast *ray, int col, int row)
{
	float			r;
	float			c;
	unsigned int	t;
	float			shadow;
	float			offset;

	if (ray->doors_v[ray->num_doors_v][3] < ray->nearest_wall_dis)
	{
		shadow = 1.0 - (fmin(ray->doors_v[ray->num_doors_v][3], 8 * B_SIZE) / (8
					* B_SIZE));
		if (ray->doors_v[ray->num_doors_v][4] == 1)
			c = round(fmod(ray->doors_v[ray->num_doors_v][1], B_SIZE) / B_SIZE
					* ray->g->img_door.w);
		else
			c = round((1 - fmod(ray->doors_v[ray->num_doors_v][1], B_SIZE)
						/ B_SIZE) * ray->g->img_door.w);
		r = round((1 - fmod(ray->doors_v[ray->num_doors_v][2] + 32
						+ ray->g->player.z, B_SIZE) / B_SIZE)
				* ray->g->img_door.h);
		offset = (ray->g->map[(int)ray->doors_v[ray->num_doors_v][6]][(int)ray->doors_v[ray->num_doors_v][5]]
				- 2) * ray->g->img_door.w;
		if ((int)c < ray->g->img_door.w / 2 && (int)c
			+ (int)offset < ray->g->img_door.w / 2)
		{
			t = ((unsigned int *)ray->g->img_door.addr)[(int)r
				* ray->g->img_door.w + (int)c + (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->g->img.addr)[row * WIN_W
					+ col] = (((int)round(((t >> 16) & 0xff)
								* shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t)&0xff) * shadow) & 0xff);
		}
		else if ((int)c > ray->g->img_door.w / 2 && (int)c
			- (int)offset > ray->g->img_door.w / 2)
		{
			t = ((unsigned int *)ray->g->img_door.addr)[(int)r
				* ray->g->img_door.w + (int)c - (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->g->img.addr)[row * WIN_W
					+ col] = (((int)round(((t >> 16) & 0xff)
								* shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t)&0xff) * shadow) & 0xff);
		}
	}
	ray->num_doors_v--;
}

void	draw_pixel(t_raycast *ray, int col, int row)
{
	float			temp_x;
	float			temp_y;
	float			r;
	float			c;
	float			shadow;
	unsigned int	t;

	ray->nearest_wall_dis = RAYCAST_RANGE * B_SIZE;
	if (ray->res_rc_3d[4] != 0 && ray->res_rc_3d[2] + ray->g->player.z >= -32
		&& ray->res_rc_3d[2] + ray->g->player.z <= 32)
	{
		shadow = 1.0 - (fmin(ray->res_rc_3d[3], 8 * B_SIZE) / (8 * B_SIZE));
		if (ray->res_rc_3d == ray->h)
		{
			if (ray->res_rc_3d[4] == 1)
			{
				c = round(fmod(ray->res_rc_3d[0], B_SIZE) / B_SIZE
						* ray->g->img_wall_no.w);
				r = round((1 - fmod(ray->res_rc_3d[2] + ray->g->player.z + 32,
								B_SIZE) / B_SIZE) * ray->g->img_wall_no.h);
				t = ((unsigned int *)ray->g->img_wall_no.addr)[(int)r
					* ray->g->img_wall_no.w + (int)c];
			}
			else
			{
				c = round((1 - fmod(ray->res_rc_3d[0], B_SIZE) / B_SIZE)
						* ray->g->img_wall_so.w);
				r = round((1 - fmod(ray->res_rc_3d[2] + ray->g->player.z + 32,
								B_SIZE) / B_SIZE) * ray->g->img_wall_so.h);
				t = ((unsigned int *)ray->g->img_wall_so.addr)[(int)r
					* ray->g->img_wall_so.w + (int)c];
			}
			((unsigned int *)ray->g->img.addr)[row * WIN_W
				+ col] = (((int)round(((t >> 16) & 0xff)
							* shadow) & 0xff) << 16)
				+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
				+ ((int)round(((t)&0xff) * shadow) & 0xff);
		}
		else
		{
			if (ray->res_rc_3d[4] == 1)
			{
				c = round(fmod(ray->res_rc_3d[1], B_SIZE) / B_SIZE
						* ray->g->img_wall_ea.w);
				r = round((1 - fmod(ray->res_rc_3d[2] + ray->g->player.z + 32,
								B_SIZE) / B_SIZE) * ray->g->img_wall_ea.h);
				t = ((unsigned int *)ray->g->img_wall_ea.addr)[(int)r
					* ray->g->img_wall_ea.w + (int)c];
			}
			else
			{
				c = round((1 - fmod(ray->res_rc_3d[1], B_SIZE) / B_SIZE)
						* ray->g->img_wall_we.w);
				r = round((1 - fmod(ray->res_rc_3d[2] + ray->g->player.z + 32,
								B_SIZE) / B_SIZE) * ray->g->img_wall_we.h);
				t = ((unsigned int *)ray->g->img_wall_we.addr)[(int)r
					* ray->g->img_wall_we.w + (int)c];
			}
			((unsigned int *)ray->g->img.addr)[row * WIN_W
				+ col] = (((int)round(((t >> 16) & 0xff)
							* shadow) & 0xff) << 16)
				+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
				+ ((int)round(((t)&0xff) * shadow) & 0xff);
		}
		ray->nearest_wall_dis = ray->res_rc_3d[3];
	}
	else if (ray->res_rc_3d[2] + ray->g->player.z < -32)
	{
		temp_x = ray->res_rc_3d[0] - ray->g->player.x;
		temp_y = ray->res_rc_3d[1] - ray->g->player.y;
		ray->res_rc_3d[0] = temp_x * (-32 - ray->g->player.z)
			/ ray->res_rc_3d[2] + ray->g->player.x;
		ray->res_rc_3d[1] = temp_y * (-32 - ray->g->player.z)
			/ ray->res_rc_3d[2] + ray->g->player.y;
		c = fmod(ray->res_rc_3d[0], B_SIZE) / B_SIZE;
		c += (c < 0);
		c = round((1 - c) * ray->g->img_floor.w);
		r = fmod(ray->res_rc_3d[1], B_SIZE) / B_SIZE;
		r += (r < 0);
		r = round((1 - r) * ray->g->img_floor.h);
		ray->res_rc_3d[3] = distance(ray->res_rc_3d[0], ray->res_rc_3d[1],
				ray->g->player.x, ray->g->player.y);
		shadow = 1.0 - (fmin(ray->res_rc_3d[3], 8 * B_SIZE) / (8 * B_SIZE));
		t = ((unsigned int *)ray->g->img_floor.addr)[(int)r
			* ray->g->img_floor.w + (int)c];
		((unsigned int *)ray->g->img.addr)[row * WIN_W
			+ col] = (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
			+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
			+ ((int)round(((t)&0xff) * shadow) & 0xff);
	}
	else if (ray->res_rc_3d[2] >= 0)
	{
		temp_x = ray->res_rc_3d[0] - ray->g->player.x;
		temp_y = ray->res_rc_3d[1] - ray->g->player.y;
		r = ray->res_rc_3d[2] / sqrt(temp_x * temp_x + temp_y * temp_y
				+ ray->res_rc_3d[2] * ray->res_rc_3d[2]);
		r = fmin(1.0, r);
		r = 1.0 - asin(r) / (M_PI / 2);
		if (temp_x != 0)
			c = (atan(temp_y / temp_x) + M_PI * (temp_x < 0) + (M_PI / 2))
				/ (M_PI * 2);
		else
			c = 1.0 / 4 + 1.0 / 2 * (temp_y < 0);
		r *= ray->g->img_sky.h;
		c *= ray->g->img_sky.w;
		((unsigned int *)ray->g->img.addr)[row * WIN_W
			+ col] = ((unsigned int *)ray->g->img_sky.addr)[((int)round(r))
			* ray->g->img_sky.w + (int)round(c)];
	}
	while (ray->num_doors_h >= 0 || ray->num_doors_v >= 0)
	{
		if (ray->num_doors_h < 0)
			do_doors_v(ray, col, row);
		else if (ray->num_doors_v < 0)
			do_doors_h(ray, col, row);
		else if (ray->doors_h[ray->num_doors_h][3] < ray->doors_v[ray->num_doors_v][3])
			do_doors_v(ray, col, row);
		else
			do_doors_h(ray, col, row);
	}
}

void	*render_section(void *arg)
{
	t_raycast	*ray;
	int			col;
	int			row;

	ray = (t_raycast *)arg;
	col = ray->col_start;
	while (col < ray->col_end)
	{
		row = 0;
		while (row < WIN_H)
		{
			raycast_3d(ray);
			draw_pixel(ray, col, row);
			ray->xyz[0] += ray->p1->x;
			ray->xyz[1] += ray->p1->y;
			ray->xyz[2] += ray->p1->z;
			row++;
		}
		ray->xyz[0] -= ray->p1->x * WIN_H;
		ray->xyz[1] -= ray->p1->y * WIN_H;
		ray->xyz[2] -= ray->p1->z * WIN_H;
		ray->xyz[0] += ray->p2->x;
		ray->xyz[1] += ray->p2->y;
		ray->xyz[2] += ray->p2->z;
		col++;
	}
	return (NULL);
}

void	draw_walls_3d(t_data *g)
{
	t_raycast	ray[NUM_THREADS];
	int			i;

	i = 0;
	while (i < NUM_THREADS)
	{
		ray[i].g = g;
		ray[i].p1 = &g->player.v_down;
		ray[i].p2 = &g->player.v_right;
		ray[i].col_start = i * (WIN_W / NUM_THREADS);
		ray[i].col_end = (i + 1) * (WIN_W / NUM_THREADS);
		ray[i].xyz[0] = g->player.dir3d.x * g->dis_p_s - g->player.v_down.x
			* WIN_H / 2 - g->player.v_right.x * WIN_W / 2 + g->player.v_right.x
			* ray[i].col_start;
		ray[i].xyz[1] = g->player.dir3d.y * g->dis_p_s - g->player.v_down.y
			* WIN_H / 2 - g->player.v_right.y * WIN_W / 2 + g->player.v_right.y
			* ray[i].col_start;
		ray[i].xyz[2] = g->player.dir3d.z * g->dis_p_s - g->player.v_down.z
			* WIN_H / 2 - g->player.v_right.z * WIN_W / 2 + g->player.v_right.z
			* ray[i].col_start;
		pthread_create(&ray[i].tid, NULL, render_section, &ray[i]);
		i++;
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(ray[i].tid, NULL);
}

void	move_doors(t_data *game)
{
	t_door	*new;
	t_door	*temp;
	t_door	*prev;

	// add new door into list
	if (game->op_door == 1)
	{
		game->coll_door_h = 0;
		game->coll_door_v = 0;
		collision(game, game->player.dir_x, game->player.dir_y, OPEN_DIS);
		if ((game->coll_door_h || game->coll_door_v)
			&& (game->map[(int)game->res_rc[5]][(int)game->res_rc[4]] == 2
				|| game->map[(int)game->res_rc[5]][(int)game->res_rc[4]] == 3))
		{
			new = gc_malloc(sizeof(t_door), &game->gc);
			new->next = game->doors;
			new->x = (int)game->res_rc[4];
			new->y = (int)game->res_rc[5];
			new->closed = (game->map[new->y][new->x] == 3);
			game->doors = new;
		}
	}
	game->op_door = 0;
	// move the doors in list one by one
	temp = game->doors;
	while (temp)
	{
		game->map[temp->y][temp->x] += ((temp->closed) * (-2) + 1) * 0.1;
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

void draw_hud(t_data *game)
{
	draw_minimap(game);
	render_image(game, &game->img_hud_health, 20, WIN_H - game->img_hud_health.h - 20);
	render_image(game, &game->img_hud_one, 20 + game->img_hud_health.w + 10, WIN_H - game->img_hud_one.h - 20);
	render_image(game, &game->img_hud_zero, 20 + game->img_hud_health.w + 20 + game->img_hud_one.w, WIN_H - game->img_hud_zero.h - 20);
	render_image(game, &game->img_hud_zero, 20 + game->img_hud_health.w + 25 + game->img_hud_one.w + game->img_hud_zero.w, WIN_H - game->img_hud_zero.h - 20);
	render_image(game, &game->img_hud_divider, 40 + game->img_hud_health.w + 25 + game->img_hud_one.w + game->img_hud_zero.w + game->img_hud_zero.w, WIN_H - game->img_hud_zero.h - 20);
	render_image(game, &game->img_hud_full_suit, 60 + game->img_hud_health.w + 25 + game->img_hud_one.w + game->img_hud_zero.w + game->img_hud_zero.w, WIN_H - game->img_hud_zero.h - 25);
    render_image(game, &game->img_hud_one, 190, WIN_H - game->img_hud_one.h - 20);
	render_image(game, &game->img_hud_zero, 208, WIN_H - game->img_hud_zero.h - 20);
	render_image(game, &game->img_hud_zero, 230, WIN_H - game->img_hud_zero.h - 20);
	render_image(game, &game->img_hud_flash_full, WIN_W - game->img_hud_flash_full.w - 20, 20);
}

int	render(t_data *game)
{
	__uint64_t	current_time;

    current_time = get_timestamp_ms();
    if (game->win_ptr != NULL && (current_time - game->time) > 1000 / FPS)
    {
        game->time = current_time;
        ft_bzero(game->img.addr, game->img.w * game->img.h * (game->img.bpp / 8));
        move_doors(game);
        move_player(game);
        draw_walls_3d(game);
		draw_hud(game);
		if (game->crowbar.state != CROWBAR_NONE)
			update_crowbar_state(game);
		else if (game->handgun.state != HANDGUN_NONE)
			update_handgun_state(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.ptr, 0, 0);
    }
    return (0);
}
