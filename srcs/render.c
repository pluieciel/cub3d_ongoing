#include "cub3D.h"

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void render_image(t_data *game, t_image *img)
{
    int i;
    int j;
    
    i = 0;
    while (i < WIN_W)
    {
        j = 0;
        while (j < WIN_H)
        {
            if (i < img->w && j < img->h)
            {
                unsigned int t = ((unsigned int *)img->addr)[j * img->w + i];
                if (t != TRANSPARENT_COLOR)
                    ((unsigned int *)game->img.addr)[j * WIN_W + i] = t;
            }
            j++;
        }
        i++;
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
        				= ((((((t >> 16) & 0xff) + 0x00) / 2) & 0xff) << 16)
        				+ ((((((t >> 8) & 0xff) + 0x00) / 2) & 0xff) << 8)
        				+ (((((t) & 0xff) + 0x00) / 2) & 0xff);
				else
					((unsigned int *)game->img.addr)[j * WIN_W + i]
        				= ((((((t >> 16) & 0xff) + 0x22) / 2) & 0xff) << 16)
        				+ ((((((t >> 8) & 0xff) + 0x22) / 2) & 0xff) << 8)
        				+ (((((t) & 0xff) + 0x22) / 2) & 0xff);
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
								= ((((((t >> 16) & 0xff) * 2 + 0x88) / 3) & 0xff) << 16)
									+ ((((((t >> 8) & 0xff) * 2 + 0x88) / 3) & 0xff) << 8)
									+ (((((t) & 0xff) * 2 + 0x88) / 3) & 0xff);
							else if (game->map[y][x] == 3)
								((unsigned int *)game->img.addr)[newi * WIN_W + newj]
								= ((((((t >> 16) & 0xff) * 2 + 0x00) / 3) & 0xff) << 16)
									+ ((((((t >> 8) & 0xff) * 2 + 0x80) / 3) & 0xff) << 8)
									+ (((((t) & 0xff) * 2 + 0x80) / 3) & 0xff);
							else if (game->map[y][x] >= 2)
								((unsigned int *)game->img.addr)[newi * WIN_W + newj]
								= ((((((t >> 16) & 0xff) * 2 + 0x80) / 3) & 0xff) << 16)
									+ ((((((t >> 8) & 0xff) * 2 + 0x00) / 3) & 0xff) << 8)
									+ (((((t) & 0xff) * 2 + 0x00) / 3) & 0xff);
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

void	move_player(t_data *game)
{
	float		oldDirX = game->player.dir[0];
	float		oldDirY = game->player.dir[1];
	float		oldDirX_3D = game->player.dir3d.x;
	float		oldDirY_3D = game->player.dir3d.y;

	game->coll_h = 0;
	game->coll_v = 0;
	t_point3D	*p1;
	t_point3D	*p2;
	if (game->key.w)
	{
		collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
		collision(game, game->player.dir[1], -game->player.dir[0], COLL_DIS);
		collision(game, -game->player.dir[1], game->player.dir[0], COLL_DIS);
		collision(game, (sqrt(2)/2) * (game->player.dir[0] - game->player.dir[1]), (sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), COLL_DIS);
		collision(game, (sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), (sqrt(2)/2) * (-game->player.dir[0] + game->player.dir[1]), COLL_DIS);

		if (!game->coll_v)
    		game->player.pos[0] += round(oldDirX * MOVE_SPEED);
    	if (!game->coll_h)
    	    game->player.pos[1] += round(oldDirY * MOVE_SPEED);
	}
	else if (game->key.s)
	{
		collision(game, -game->player.dir[0], -game->player.dir[1], COLL_DIS);
		collision(game, game->player.dir[1], -game->player.dir[0], COLL_DIS);
		collision(game, -game->player.dir[1], game->player.dir[0], COLL_DIS);
		collision(game, -(sqrt(2)/2) * (game->player.dir[0] - game->player.dir[1]), -(sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), COLL_DIS);
		collision(game, -(sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), -(sqrt(2)/2) * (-game->player.dir[0] + game->player.dir[1]), COLL_DIS);

		if (!game->coll_v)
    		game->player.pos[0] -= round(oldDirX * MOVE_SPEED);
    	if (!game->coll_h)
    	    game->player.pos[1] -= round(oldDirY * MOVE_SPEED);
	}
	if (game->key.a)
	{
		collision(game, game->player.dir[1], -game->player.dir[0], COLL_DIS);
		collision(game, -game->player.dir[0], -game->player.dir[1], COLL_DIS);
		collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
		collision(game, (sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), (sqrt(2)/2) * (-game->player.dir[0] + game->player.dir[1]), COLL_DIS);
		collision(game, -(sqrt(2)/2) * (game->player.dir[0] - game->player.dir[1]), -(sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), COLL_DIS);
		
		if (!game->coll_v)
    		game->player.pos[0] += round(oldDirY * MOVE_SPEED);
    	if (!game->coll_h)
    	    game->player.pos[1] -= round(oldDirX * MOVE_SPEED);
	}
	else if (game->key.d)
	{
		collision(game, -game->player.dir[1], game->player.dir[0], COLL_DIS);
		collision(game, -game->player.dir[0], -game->player.dir[1], COLL_DIS);
		collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
		collision(game, -(sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), -(sqrt(2)/2) * (-game->player.dir[0] + game->player.dir[1]), COLL_DIS);
		collision(game, (sqrt(2)/2) * (game->player.dir[0] - game->player.dir[1]), (sqrt(2)/2) * (game->player.dir[0] + game->player.dir[1]), COLL_DIS);

		if (!game->coll_v)
    		game->player.pos[0] -= round(oldDirY * MOVE_SPEED);
    	if (!game->coll_h)
    	    game->player.pos[1] += round(oldDirX * MOVE_SPEED);
	}
	if (game->key.left)
	{
		game->player.dir[0] = oldDirX * cos(-ROT_SPEED) - oldDirY * sin(-ROT_SPEED);
		game->player.dir[1] = oldDirX * sin(-ROT_SPEED) + oldDirY * cos(-ROT_SPEED);
		game->player.dir3d.x = oldDirX_3D * cos(-ROT_SPEED) - oldDirY_3D * sin(-ROT_SPEED);
		game->player.dir3d.y = oldDirX_3D * sin(-ROT_SPEED) + oldDirY_3D * cos(-ROT_SPEED);
		if (game->player.dir[0] > 0)
			game->player.dir3d.angle = atan(game->player.dir[1] / game->player.dir[0]);
		else if (game->player.dir[0] < 0)
			game->player.dir3d.angle = atan(game->player.dir[1] / game->player.dir[0]) + M_PI;
		else
			game->player.dir3d.angle = ((game->player.dir[1] > 0) * 2 - 1) * M_PI / 2;
	}
	else if (game->key.right)
	{
		game->player.dir[0] = oldDirX * cos(ROT_SPEED) - oldDirY * sin(ROT_SPEED);
		game->player.dir[1] = oldDirX * sin(ROT_SPEED) + oldDirY * cos(ROT_SPEED);
		game->player.dir3d.x = oldDirX_3D * cos(ROT_SPEED) - oldDirY_3D * sin(ROT_SPEED);
		game->player.dir3d.y = oldDirX_3D * sin(ROT_SPEED) + oldDirY_3D * cos(ROT_SPEED);
		if (game->player.dir[0] > 0)
			game->player.dir3d.angle = atan(game->player.dir[1] / game->player.dir[0]);
		else if (game->player.dir[0] < 0)
			game->player.dir3d.angle = atan(game->player.dir[1] / game->player.dir[0]) + M_PI;
		else
			game->player.dir3d.angle = ((game->player.dir[1] > 0) * 2 - 1) * M_PI / 2;
	}
	if (game->key.up && game->player.dir3d.z < 0.95)
	{
		p1 = ro_on_z_to_xz(game->player.dir3d);
		p2 = ro_on_y(*p1, ROT_SPEED);
		free(p1);
		p1 = ro_back_on_z(*p2);
		free(p2);
		game->player.dir3d.x = p1->x;
		game->player.dir3d.y = p1->y;
		game->player.dir3d.z = p1->z;
		free(p1);
	}
	else if (game->key.down && game->player.dir3d.z > -0.95)
	{
		p1 = ro_on_z_to_xz(game->player.dir3d);
		p2 = ro_on_y(*p1, -ROT_SPEED);
		free(p1);
		p1 = ro_back_on_z(*p2);
		free(p2);
		game->player.dir3d.x = p1->x;
		game->player.dir3d.y = p1->y;
		game->player.dir3d.z = p1->z;
		free(p1);
	}
}

void	do_doors_h(t_raycast *ray, int col, int row)
{
	float	r;
	float	c;
	unsigned int	t;
	float	shadow;
	float	offset;

	if (ray->doors_h[ray->num_doors_h][3] < ray->nearest_wall_dis)
	{
		shadow = 1.0 - (fmin(ray->doors_h[ray->num_doors_h][3], 8 * B_SIZE) / (8 * B_SIZE));
		if (ray->doors_h[ray->num_doors_h][4] == 1)
			c = round(fmod(ray->doors_h[ray->num_doors_h][0], B_SIZE) / B_SIZE * ray->game->img_door.w);
		else
			c = round((1 - fmod(ray->doors_h[ray->num_doors_h][0], B_SIZE) / B_SIZE) * ray->game->img_door.w);
		r = round((1 - fmod(ray->doors_h[ray->num_doors_h][2] + 32, B_SIZE) / B_SIZE) * ray->game->img_door.h);
		offset = (ray->game->map[(int)ray->doors_h[ray->num_doors_h][6]][(int)ray->doors_h[ray->num_doors_h][5]] - 2) * ray->game->img_door.w;
		if ((int)c < ray->game->img_door.w / 2 && (int)c + (int)offset < ray->game->img_door.w / 2)
		{
			t = ((unsigned int *)ray->game->img_door.addr)[(int)r * ray->game->img_door.w + (int)c + (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
		else if ((int)c > ray->game->img_door.w / 2 && (int)c - (int)offset > ray->game->img_door.w / 2)
		{
			t = ((unsigned int *)ray->game->img_door.addr)[(int)r * ray->game->img_door.w + (int)c - (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
	}
	ray->num_doors_h--;
}

void	do_doors_v(t_raycast *ray, int col, int row)
{
	float	r;
	float	c;
	unsigned int	t;
	float	shadow;
	float	offset;

	if (ray->doors_v[ray->num_doors_v][3] < ray->nearest_wall_dis)
	{
		shadow = 1.0 - (fmin(ray->doors_v[ray->num_doors_v][3], 8 * B_SIZE) / (8 * B_SIZE));
		if (ray->doors_v[ray->num_doors_v][4] == 1)
			c = round(fmod(ray->doors_v[ray->num_doors_v][1], B_SIZE) / B_SIZE * ray->game->img_door.w);
		else
			c = round((1 - fmod(ray->doors_v[ray->num_doors_v][1], B_SIZE) / B_SIZE) * ray->game->img_door.w);
		r = round((1 - fmod(ray->doors_v[ray->num_doors_v][2] + 32, B_SIZE) / B_SIZE) * ray->game->img_door.h);
		offset = (ray->game->map[(int)ray->doors_v[ray->num_doors_v][6]][(int)ray->doors_v[ray->num_doors_v][5]] - 2) * ray->game->img_door.w;
		if ((int)c < ray->game->img_door.w / 2 && (int)c + (int)offset < ray->game->img_door.w / 2)
		{
			t = ((unsigned int *)ray->game->img_door.addr)[(int)r * ray->game->img_door.w + (int)c + (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
		else if ((int)c > ray->game->img_door.w / 2 && (int)c - (int)offset > ray->game->img_door.w / 2)
		{
			t = ((unsigned int *)ray->game->img_door.addr)[(int)r * ray->game->img_door.w + (int)c - (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
	}
	ray->num_doors_v--;
}

void	draw_pixel(t_raycast *ray, int col, int row)
{
	float	temp_x;
	float	temp_y;
	float	r;
	float	c;
	float	shadow;
	unsigned int	t;

	ray->nearest_wall_dis = RAYCAST_RANGE * B_SIZE;
	if (ray->res_rc_3d[4] != 0
	&& ray->res_rc_3d[2] >= -32 && ray->res_rc_3d[2] <= 32)
	{
		shadow = 1.0 - (fmin(ray->res_rc_3d[3], 8 * B_SIZE) / (8 * B_SIZE));
		if (ray->res_rc_3d == ray->res_rc_h_3d)
		{
			if (ray->res_rc_3d[4] == 1)
			{
				c = round(fmod(ray->res_rc_3d[0], B_SIZE) / B_SIZE * ray->game->img_wall_no.w);
				r = round((1 - fmod(ray->res_rc_3d[2] + 32, B_SIZE) / B_SIZE) * ray->game->img_wall_no.h);
				t = ((unsigned int *)ray->game->img_wall_no.addr)[(int)r * ray->game->img_wall_no.w + (int)c];
			}
			else
			{
				c = round((1 - fmod(ray->res_rc_3d[0], B_SIZE) / B_SIZE) * ray->game->img_wall_so.w);
				r = round((1 - fmod(ray->res_rc_3d[2] + 32, B_SIZE) / B_SIZE) * ray->game->img_wall_so.h);
				t = ((unsigned int *)ray->game->img_wall_so.addr)[(int)r * ray->game->img_wall_so.w + (int)c];
			}
			((unsigned int *)ray->game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
		else
		{
			if (ray->res_rc_3d[4] == 1)
			{
				c = round(fmod(ray->res_rc_3d[1], B_SIZE) / B_SIZE * ray->game->img_wall_ea.w);
				r = round((1 - fmod(ray->res_rc_3d[2] + 32, B_SIZE) / B_SIZE) * ray->game->img_wall_ea.h);
				t = ((unsigned int *)ray->game->img_wall_ea.addr)[(int)r * ray->game->img_wall_ea.w + (int)c];
			}
			else
			{
				c = round((1 - fmod(ray->res_rc_3d[1], B_SIZE) / B_SIZE) * ray->game->img_wall_we.w);
				r = round((1 - fmod(ray->res_rc_3d[2] + 32, B_SIZE) / B_SIZE) * ray->game->img_wall_we.h);
				t = ((unsigned int *)ray->game->img_wall_we.addr)[(int)r * ray->game->img_wall_we.w + (int)c];
			}
			((unsigned int *)ray->game->img.addr)[row * WIN_W + col]
				= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t) & 0xff) * shadow) & 0xff);
		}
		ray->nearest_wall_dis = ray->res_rc_3d[3];
	}
	else if (ray->res_rc_3d[2] < -32)
	{
		temp_x = ray->res_rc_3d[0] - ray->game->player.pos[0];
		temp_y = ray->res_rc_3d[1] - ray->game->player.pos[1];
		ray->res_rc_3d[0] = temp_x * -32 / ray->res_rc_3d[2] + ray->game->player.pos[0];
		ray->res_rc_3d[1] = temp_y * -32 / ray->res_rc_3d[2] + ray->game->player.pos[1];
		c = fmod(ray->res_rc_3d[0], B_SIZE) / B_SIZE;
		c += (c < 0);
		c = round((1 - c) * ray->game->img_floor.w);
		r = fmod(ray->res_rc_3d[1], B_SIZE) / B_SIZE;
		r += (r < 0);
		r = round((1 - r) * ray->game->img_floor.h);
		ray->res_rc_3d[3] = distance(ray->res_rc_3d[0], ray->res_rc_3d[1], ray->game->player.pos[0], ray->game->player.pos[1]);
		shadow = 1.0 - (fmin(ray->res_rc_3d[3], 8 * B_SIZE) / (8 * B_SIZE));
		t = ((unsigned int *)ray->game->img_floor.addr)[(int)r * ray->game->img_floor.w + (int)c];
		((unsigned int *)ray->game->img.addr)[row * WIN_W + col]
		= (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
			+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
			+ ((int)round(((t) & 0xff) * shadow) & 0xff);
	}
	else if (ray->res_rc_3d[2] >= 0)
	{
		temp_x = ray->res_rc_3d[0] - ray->game->player.pos[0];
		temp_y = ray->res_rc_3d[1] - ray->game->player.pos[1];
		r = ray->res_rc_3d[2] / sqrt(temp_x * temp_x + temp_y * temp_y + ray->res_rc_3d[2] * ray->res_rc_3d[2]);
		r = fmin(1.0, r);
		r = 1.0 - asin(r) / (M_PI / 2);
		if (temp_x != 0)
			c = (atan(temp_y / temp_x) + M_PI * (temp_x < 0) + (M_PI / 2)) / (M_PI * 2);
		else
			c = 1.0 / 4 + 1.0 / 2 * (temp_y < 0);
		r *= ray->game->img_sky.h;
		c *= ray->game->img_sky.w;
		((unsigned int *)ray->game->img.addr)[row * WIN_W + col] = ((unsigned int *)ray->game->img_sky.addr)[((int)round(r)) * ray->game->img_sky.w + (int)round(c)];
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
	t_raycast *ray = (t_raycast *)arg;
	int col, row;
	for (col = ray->col_start; col < ray->col_end; col++)
	{
		row = 0;
		while (row < WIN_H)
		{
			raycast_3D(ray);
			draw_pixel(ray, col, row);
			ray->temp[0] += ray->p1->x;
			ray->temp[1] += ray->p1->y;
			ray->temp[2] += ray->p1->z;
			row++;
		}
		ray->temp[0] -= ray->p1->x * WIN_H;
		ray->temp[1] -= ray->p1->y * WIN_H;
		ray->temp[2] -= ray->p1->z * WIN_H;
		ray->temp[0] += ray->p2->x;
		ray->temp[1] += ray->p2->y;
		ray->temp[2] += ray->p2->z;
	}
	return (NULL);
}

void	draw_walls_3D(t_data *game)
{
	t_point3D	*p1, *p2;
	t_raycast ray[NUM_THREADS];
	p1 = ro_on_z_to_xz(game->player.dir3d);
	p2 = ro_on_y(*p1, -M_PI / 2);
	free(p1);
	p1 = ro_back_on_z(*p2); // toward down on screen
	free(p2);
	p2 = cross(game->player.dir3d, *p1); // toward right on screen
	int	i;
	for (i = 0; i < NUM_THREADS; i++)
	{
		ray[i].game = game;
		ray[i].p1 = p1;
		ray[i].p2 = p2;
		ray[i].col_start = i * (WIN_W / NUM_THREADS);
		ray[i].col_end = (i + 1) * (WIN_W / NUM_THREADS);
		ray[i].temp[0] = -p1->x * WIN_H / 2 - p2->x * WIN_W / 2 + p2->x * ray[i].col_start;
		ray[i].temp[1] = -p1->y * WIN_H / 2 - p2->y * WIN_W / 2 + p2->y * ray[i].col_start;
		ray[i].temp[2] = -p1->z * WIN_H / 2 - p2->z * WIN_W / 2 + p2->z * ray[i].col_start;
		pthread_create(&ray[i].tid, NULL, render_section, &ray[i]);
	}
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(ray[i].tid, NULL);
	}
	free(p1);
	free(p2);
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
		collision(game, game->player.dir[0], game->player.dir[1], OPEN_DIS);
		if ((game->coll_door_h || game->coll_door_v)
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

int render(t_data *game)
{
    __uint64_t current_time;

    current_time = get_timestamp_ms();
    if (game->win_ptr != NULL && (current_time - game->time) > 1000 / FPS)
    {
        game->time = current_time;
        ft_bzero(game->img.addr, game->img.w * game->img.h * (game->img.bpp / 8));
        move_doors(game);
        move_player(game);
        draw_walls_3D(game);
        draw_minimap(game);
		update_crowbar_state(game);
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.ptr, 0, 0);
    }
    return (0);
}
