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

	if (!img)
		return ;
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

void	collision(t_data *game, float dir_x, float dir_y, int coll_dis)
{
	raycast(game, dir_x, dir_y, (coll_dis == OPEN_DIS));
	if (game->res_rc_h.dis < coll_dis && game->res_rc_h.dis < game->res_rc_v.dis)
	{
		game->coll_wall_h = 1;
		if (coll_dis == OPEN_DIS)
			game->coll_door_h = 1;
	}
	if (game->res_rc_v.dis < coll_dis && game->res_rc_v.dis < game->res_rc_h.dis)
	{
		game->coll_wall_v = 1;
		if (coll_dis == OPEN_DIS)
			game->coll_door_v = 1;
	}
}

void	do_jump(t_data *game)
{
	if (game->player.z == 0 && game->player.jump_velocity == 0)
		game->player.jump_velocity = JUMP_VELOCITY;
	else if (game->player.z < 0)
	{
		game->player.jump_velocity = 0;
		game->player.z = 0;
		game->key.space = 0;
	}
	else
	{
		game->player.z += game->player.jump_velocity * game->timestep / 1000;
		game->player.jump_velocity -= GRAVITY * game->timestep / 1000;
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
	game->coll_wall_h = 0;
	game->coll_wall_v = 0;
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
		if (!game->coll_wall_v)
			game->player.x += round(oldDirX * game->player.speed);
		if (!game->coll_wall_h)
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
		if (!game->coll_wall_v)
			game->player.x -= round(oldDirX * game->player.speed);
		if (!game->coll_wall_h)
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
		if (!game->coll_wall_v)
			game->player.x += round(oldDirY * game->player.speed);
		if (!game->coll_wall_h)
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
		if (!game->coll_wall_v)
			game->player.x -= round(oldDirY * game->player.speed);
		if (!game->coll_wall_h)
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
		game->player.z = -10;
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
	if (ray->res_rc->dir != 0 && ray->res_rc->z + ray->g->player.z >= -32
		&& ray->res_rc->z + ray->g->player.z <= 32)
	{
		shadow = 1.0 - (fmin(ray->res_rc->dis, 8 * B_SIZE) / (8 * B_SIZE));
		if (ray->res_rc == &ray->res_rc_h)
		{
			if (ray->res_rc->dir == 1)
			{
				c = round(fmod(ray->res_rc->x, B_SIZE) / B_SIZE
						* ray->g->img_wall_no.w);
				r = round((1 - fmod(ray->res_rc->z + ray->g->player.z + 32,
								B_SIZE) / B_SIZE) * ray->g->img_wall_no.h);
				t = ((unsigned int *)ray->g->img_wall_no.addr)[(int)r
					* ray->g->img_wall_no.w + (int)c];
			}
			else
			{
				c = round((1 - fmod(ray->res_rc->x, B_SIZE) / B_SIZE)
						* ray->g->img_wall_so.w);
				r = round((1 - fmod(ray->res_rc->z + ray->g->player.z + 32,
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
			if (ray->res_rc->dir == 1)
			{
				c = round(fmod(ray->res_rc->y, B_SIZE) / B_SIZE
						* ray->g->img_wall_ea.w);
				r = round((1 - fmod(ray->res_rc->z + ray->g->player.z + 32,
								B_SIZE) / B_SIZE) * ray->g->img_wall_ea.h);
				t = ((unsigned int *)ray->g->img_wall_ea.addr)[(int)r
					* ray->g->img_wall_ea.w + (int)c];
			}
			else
			{
				c = round((1 - fmod(ray->res_rc->y, B_SIZE) / B_SIZE)
						* ray->g->img_wall_we.w);
				r = round((1 - fmod(ray->res_rc->z + ray->g->player.z + 32,
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
		ray->nearest_wall_dis = ray->res_rc->dis;
	}
	else if (ray->res_rc->z + ray->g->player.z < -32)
	{
		temp_x = ray->res_rc->x - ray->g->player.x;
		temp_y = ray->res_rc->y - ray->g->player.y;
		ray->res_rc->x = temp_x * (-32 - ray->g->player.z)
			/ ray->res_rc->z + ray->g->player.x;
		ray->res_rc->y = temp_y * (-32 - ray->g->player.z)
			/ ray->res_rc->z + ray->g->player.y;
		c = fmod(ray->res_rc->x, B_SIZE) / B_SIZE;
		c += (c < 0);
		c = round((1 - c) * ray->g->img_floor.w);
		r = fmod(ray->res_rc->y, B_SIZE) / B_SIZE;
		r += (r < 0);
		r = round((1 - r) * ray->g->img_floor.h);
		ray->res_rc->dis = distance(ray->res_rc->x, ray->res_rc->y,
				ray->g->player.x, ray->g->player.y);
		shadow = 1.0 - (fmin(ray->res_rc->dis, 8 * B_SIZE) / (8 * B_SIZE));
		t = ((unsigned int *)ray->g->img_floor.addr)[(int)r
			* ray->g->img_floor.w + (int)c];
		((unsigned int *)ray->g->img.addr)[row * WIN_W
			+ col] = (((int)round(((t >> 16) & 0xff) * shadow) & 0xff) << 16)
			+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
			+ ((int)round(((t)&0xff) * shadow) & 0xff);
	}
	else if (ray->res_rc->z >= 0)
	{
		temp_x = ray->res_rc->x - ray->g->player.x;
		temp_y = ray->res_rc->y - ray->g->player.y;
		r = ray->res_rc->z / sqrt(temp_x * temp_x + temp_y * temp_y
				+ ray->res_rc->z * ray->res_rc->z);
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
	col = ray->col_start - 1;
	while (++col < ray->col_end)
	{
		row = -1;
		while (++row < WIN_H)
		{
			raycast_3d(ray);
			draw_pixel(ray, col, row);
			ray->p.x += ray->p1->x;
			ray->p.y += ray->p1->y;
			ray->p.z += ray->p1->z;
		}
		ray->p.x -= ray->p1->x * WIN_H;
		ray->p.y -= ray->p1->y * WIN_H;
		ray->p.z -= ray->p1->z * WIN_H;
		ray->p.x += ray->p2->x;
		ray->p.y += ray->p2->y;
		ray->p.z += ray->p2->z;
	}
	return (NULL);
}

void	draw_walls_3d(t_data *g)
{
	t_raycast	ray[NUM_THREADS];
	int			i;

	i = -1;
	while (++i < NUM_THREADS)
	{
		ray[i].g = g;
		ray[i].p1 = &g->player.v_down;
		ray[i].p2 = &g->player.v_right;
		ray[i].col_start = i * (WIN_W / NUM_THREADS);
		ray[i].col_end = (i + 1) * (WIN_W / NUM_THREADS);
		ray[i].p.x = g->player.dir3d.x * g->dis_p_s - g->player.v_down.x
			* WIN_H / 2 - g->player.v_right.x * WIN_W / 2 + g->player.v_right.x
			* ray[i].col_start;
		ray[i].p.y = g->player.dir3d.y * g->dis_p_s - g->player.v_down.y
			* WIN_H / 2 - g->player.v_right.y * WIN_W / 2 + g->player.v_right.y
			* ray[i].col_start;
		ray[i].p.z = g->player.dir3d.z * g->dis_p_s - g->player.v_down.z
			* WIN_H / 2 - g->player.v_right.z * WIN_W / 2 + g->player.v_right.z
			* ray[i].col_start;
		pthread_create(&ray[i].thread, NULL, render_section, &ray[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(ray[i].thread, NULL);
}

void	move_doors(t_data *game)
{
	t_door	*new;
	t_door	*temp;
	t_door	*prev;

	// add new door into list
	if (game->key.e == 1)
	{
		game->coll_door_h = 0;
		game->coll_door_v = 0;
		collision(game, game->player.dir_x, game->player.dir_y, OPEN_DIS);
		if ((game->coll_door_h || game->coll_door_v)
			&& (game->map[(int)game->res_rc->map_y][(int)game->res_rc->map_x] == 2
				|| game->map[(int)game->res_rc->map_y][(int)game->res_rc->map_x] == 3))
		{
			new = gc_malloc(sizeof(t_door), &game->gc);
			new->next = game->doors;
			new->x = (int)game->res_rc->map_x;
			new->y = (int)game->res_rc->map_y;
			new->closed = (game->map[new->y][new->x] == 3);
			game->doors = new;
		}
	}
	game->key.e = 0;
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

t_image *get_hud_image(t_data *game, char *name)
{
	t_list *hud_elem;
	t_hud *hud;

	hud_elem = game->hud_elem;
	while (hud_elem)
	{
		hud = (t_hud *)hud_elem->content;
		if (!ft_strcmp(hud->name, name))
			return hud->img;
		hud_elem = hud_elem->next;
	}
	return (NULL);
}

void render_hud_image(t_data *game, char *name, int *x, int y)
{
	t_image *img;

	img = get_hud_image(game, name);
	if (img)
	{
		render_image(game, img, WIN_W - img->w - *x, WIN_H - img->h - y);
		*x += img->w; 
	}
}

void draw_hud(t_data *game)
{
	int x;

	x = WIN_W - 40;
	render_hud_image(game, "hud_cross.xpm", &x, 20);
	x -= 45;
	render_hud_image(game, "hud_number_1.xpm", &x, 20);
	x -= 30;
	render_hud_image(game, "hud_number_0.xpm", &x, 20);
	x -= 35;
	render_hud_image(game, "hud_number_0.xpm", &x, 20);
	x -= 35;
	render_hud_image(game, "hud_divider.xpm", &x, 20);
	x -= 50;
	render_hud_image(game, "hud_suit_full.xpm", &x, 15);
	x -= 50;
	render_hud_image(game, "hud_number_1.xpm", &x, 20);
	x -= 30;
	render_hud_image(game, "hud_number_0.xpm", &x, 20);
	x -= 35;
	render_hud_image(game, "hud_number_0.xpm", &x, 20);
	draw_minimap(game);
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
		update_animation(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.ptr, 0, 0);
    }
    return (0);
}
