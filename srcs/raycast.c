#include "cub3D.h"

float	raycast_h(t_data *game, float x, float y, int type)
{
	float	dir_x;
	float	dir_y;
	int		range;

	range = 0;
	dir_x = x;
	dir_y = y;
	if (dir_y < 0)
	{
		game->res_rc_h[1] = game->player.pos[1] - game->player.pos[1] % B_SIZE;
		game->res_rc_h[0] = game->player.pos[0] - (game->player.pos[1] % B_SIZE) * dir_x / dir_y;
		game->res_rc_h[3] = -1;
	}
	else if (dir_y > 0)
	{
		game->res_rc_h[1] = game->player.pos[1] + B_SIZE - game->player.pos[1] % B_SIZE;
		game->res_rc_h[0] = game->player.pos[0] + (B_SIZE - game->player.pos[1] % B_SIZE) * dir_x / dir_y;
		game->res_rc_h[3] = 1;
	}
	else
	{
		range = RAYCAST_RANGE;
		game->res_rc_h[0] = game->player.pos[0];
		game->res_rc_h[1] = game->player.pos[1];
		game->res_rc_h[3] = 0;
	}
	while (range < RAYCAST_RANGE && game->res_rc_h[0] / B_SIZE > 0 && game->res_rc_h[0] / B_SIZE < game->map_w)
	{
		game->res_rc_h[5] = (int)game->res_rc_h[1] / B_SIZE - (dir_y < 0);
		game->res_rc_h[4] = (int)game->res_rc_h[0] / B_SIZE;
		if (dir_y != 0
		&& game->res_rc_h[5] > 0 && game->res_rc_h[5] < game->map_h
		&& (game->map[(int)game->res_rc_h[5]][(int)game->res_rc_h[4]] == 1
		|| game->map[(int)game->res_rc_h[5]][(int)game->res_rc_h[4]] == 2
		|| (type && game->map[(int)game->res_rc_h[5]][(int)game->res_rc_h[4]] == 3)))
			return distance(game->res_rc_h[0], game->res_rc_h[1], game->player.pos[0], game->player.pos[1]);
		range++;
		game->res_rc_h[0] += dir_x / fabs(dir_y) * B_SIZE;
		game->res_rc_h[1] += ((dir_y > 0) * 2 - 1) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

float	raycast_v(t_data *game, float x, float y, int type)
{
	float	dir_x;
	float	dir_y;
	int		range;

	range = 0;
	dir_x = x;
	dir_y = y;
	if (dir_x < 0)
	{
		game->res_rc_v[0] = game->player.pos[0] - game->player.pos[0] % B_SIZE;
		game->res_rc_v[1] = game->player.pos[1] - (game->player.pos[0] % B_SIZE) * dir_y / dir_x;
		game->res_rc_v[3] = -1;
	}
	else if (dir_x > 0)
	{
		game->res_rc_v[0] = game->player.pos[0] + B_SIZE - game->player.pos[0] % B_SIZE;
		game->res_rc_v[1] = game->player.pos[1] + (B_SIZE - game->player.pos[0] % B_SIZE) * dir_y / dir_x;
		game->res_rc_v[3] = 1;
	}
	else
	{
		range = RAYCAST_RANGE;
		game->res_rc_v[0] = game->player.pos[0];
		game->res_rc_v[1] = game->player.pos[1];
		game->res_rc_v[3] = 0;
	}
	while (range < RAYCAST_RANGE && game->res_rc_v[1] / B_SIZE > 0 && game->res_rc_v[1] / B_SIZE < game->map_h)
	{
		game->res_rc_v[5] = (int)game->res_rc_v[1] / B_SIZE;
		game->res_rc_v[4] = (int)game->res_rc_v[0] / B_SIZE - (dir_x < 0);
		if (dir_x != 0
		&& game->res_rc_v[4] > 0 && game->res_rc_v[4] < game->map_w
		&& (game->map[(int)game->res_rc_v[5]][(int)game->res_rc_v[4]] == 1
		|| game->map[(int)game->res_rc_v[5]][(int)game->res_rc_v[4]] == 2
		|| (type && game->map[(int)game->res_rc_v[5]][(int)game->res_rc_v[4]] == 3)))
			return distance(game->res_rc_v[0], game->res_rc_v[1], game->player.pos[0], game->player.pos[1]);
		range++;
		game->res_rc_v[1] += dir_y / fabs(dir_x) * B_SIZE;
		game->res_rc_v[0] += ((dir_x > 0) * 2 - 1) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

void	raycast(t_data *game, float x, float y, int type)
{
	game->res_rc_h[2] = raycast_h(game, x, y, type);
	game->res_rc_v[2] = raycast_v(game, x, y, type);
	if (game->res_rc_h[2] < game->res_rc_v[2])
		game->res_rc = game->res_rc_h;
	else
		game->res_rc = game->res_rc_v;
}

float	raycast_h_3D(t_raycast *ray)
{
	float	dir_x;
	float	dir_y;
	float	dir_z;
	int		range;
	int		type;

	range = 0;
	dir_x = ray->game->player.dir3D.x * ray->game->dis_p_s + ray->temp[0];
	dir_y = ray->game->player.dir3D.y * ray->game->dis_p_s + ray->temp[1];
	dir_z = ray->game->player.dir3D.z * ray->game->dis_p_s + ray->temp[2];
	if (dir_y < 0)
	{
		ray->res_rc_h_3D[1] = ray->game->player.pos[1] - ray->game->player.pos[1] % B_SIZE;
		ray->res_rc_h_3D[0] = ray->game->player.pos[0] - (ray->game->player.pos[1] % B_SIZE) * dir_x / dir_y;
		ray->res_rc_h_3D[2] = (ray->game->player.pos[1] % B_SIZE) * dir_z / -dir_y;
		ray->res_rc_h_3D[4] = 1;
	}
	else if (dir_y > 0)
	{
		ray->res_rc_h_3D[1] = ray->game->player.pos[1] + B_SIZE - ray->game->player.pos[1] % B_SIZE;
		ray->res_rc_h_3D[0] = ray->game->player.pos[0] + (B_SIZE - ray->game->player.pos[1] % B_SIZE) * dir_x / dir_y;
		ray->res_rc_h_3D[2] = (B_SIZE - ray->game->player.pos[1] % B_SIZE) * dir_z / dir_y;
		ray->res_rc_h_3D[4] = -1;
	}
	else
	{
		range = RAYCAST_RANGE;
		ray->res_rc_h_3D[0] = ray->game->player.pos[0];
		ray->res_rc_h_3D[1] = ray->game->player.pos[1];
		ray->res_rc_h_3D[4] = 0;
	}
	while (range < RAYCAST_RANGE
	&& ray->res_rc_h_3D[0] / B_SIZE > 0 && ray->res_rc_h_3D[0] / B_SIZE < ray->game->map_w
	&& ray->res_rc_h_3D[2] <= B_SIZE / 2 && ray->res_rc_h_3D[2] >= -B_SIZE / 2)
	{
		ray->res_rc_h_3D[5] = (int)ray->res_rc_h_3D[0] / B_SIZE;
		ray->res_rc_h_3D[6] = (int)ray->res_rc_h_3D[1] / B_SIZE - (dir_y < 0);
		if (dir_y != 0
		&& ray->res_rc_h_3D[6] >= 0 && ray->res_rc_h_3D[6] < ray->game->map_h)
		{
			type = ray->game->map[(int)ray->res_rc_h_3D[6]][(int)ray->res_rc_h_3D[5]];
			if (type == 1)
				return distance(ray->res_rc_h_3D[0], ray->res_rc_h_3D[1], ray->game->player.pos[0], ray->game->player.pos[1]);
			else if (type >= 2)
			{
				ray->num_doors_h++;
				ray->doors_h[ray->num_doors_h][0] = ray->res_rc_h_3D[0];
				ray->doors_h[ray->num_doors_h][1] = ray->res_rc_h_3D[1];
				ray->doors_h[ray->num_doors_h][2] = ray->res_rc_h_3D[2];
				ray->doors_h[ray->num_doors_h][3] = distance(ray->res_rc_h_3D[0], ray->res_rc_h_3D[1], ray->game->player.pos[0], ray->game->player.pos[1]);
				ray->doors_h[ray->num_doors_h][4] = ray->res_rc_h_3D[4];
				ray->doors_h[ray->num_doors_h][5] = ray->res_rc_h_3D[5];
				ray->doors_h[ray->num_doors_h][6] = ray->res_rc_h_3D[6];
			}
		}
		range++;
		ray->res_rc_h_3D[0] += dir_x / fabs(dir_y) * B_SIZE;
		ray->res_rc_h_3D[1] += ((dir_y > 0) * 2 - 1) * B_SIZE;
		ray->res_rc_h_3D[2] += dir_z / fabs(dir_y) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

float	raycast_v_3D(t_raycast *ray)
{
	float	dir_x;
	float	dir_y;
	float	dir_z;
	int		range;
	int		type;

	range = 0;
	dir_x = ray->game->player.dir3D.x * ray->game->dis_p_s + ray->temp[0];
	dir_y = ray->game->player.dir3D.y * ray->game->dis_p_s + ray->temp[1];
	dir_z = ray->game->player.dir3D.z * ray->game->dis_p_s + ray->temp[2];
	if (dir_x < 0)
	{
		ray->res_rc_v_3D[0] = ray->game->player.pos[0] - ray->game->player.pos[0] % B_SIZE;
		ray->res_rc_v_3D[1] = ray->game->player.pos[1] - (ray->game->player.pos[0] % B_SIZE) * dir_y / dir_x;
		ray->res_rc_v_3D[2] = (ray->game->player.pos[0] % B_SIZE) * dir_z / -dir_x;
		ray->res_rc_v_3D[4] = -1;
	}
	else if (dir_x > 0)
	{
		ray->res_rc_v_3D[0] = ray->game->player.pos[0] + B_SIZE - ray->game->player.pos[0] % B_SIZE;
		ray->res_rc_v_3D[1] = ray->game->player.pos[1] + (B_SIZE - ray->game->player.pos[0] % B_SIZE) * dir_y / dir_x;
		ray->res_rc_v_3D[2] = (B_SIZE - ray->game->player.pos[0] % B_SIZE) * dir_z / dir_x;
		ray->res_rc_v_3D[4] = 1;
	}
	else
	{
		range = RAYCAST_RANGE;
		ray->res_rc_v_3D[0] = ray->game->player.pos[0];
		ray->res_rc_v_3D[1] = ray->game->player.pos[1];
		ray->res_rc_v_3D[4] = 0;
	}
	while (range < RAYCAST_RANGE
	&& ray->res_rc_v_3D[1] / B_SIZE > 0 && ray->res_rc_v_3D[1] / B_SIZE < ray->game->map_h
	&& ray->res_rc_v_3D[2] <= B_SIZE / 2 && ray->res_rc_v_3D[2] >= -B_SIZE / 2)
	{
		ray->res_rc_v_3D[5] = (int)ray->res_rc_v_3D[0] / B_SIZE - (dir_x < 0);
		ray->res_rc_v_3D[6] = (int)ray->res_rc_v_3D[1] / B_SIZE;
		if (dir_x != 0
		&& ray->res_rc_v_3D[5] >= 0 && ray->res_rc_v_3D[5] < ray->game->map_w)
		{
			type = ray->game->map[(int)ray->res_rc_v_3D[6]][(int)ray->res_rc_v_3D[5]];
			if (type == 1)
				return distance(ray->res_rc_v_3D[0], ray->res_rc_v_3D[1], ray->game->player.pos[0], ray->game->player.pos[1]);
			else if (type >= 2)
			{
				ray->num_doors_v++;
				ray->doors_v[ray->num_doors_v][0] = ray->res_rc_v_3D[0];
				ray->doors_v[ray->num_doors_v][1] = ray->res_rc_v_3D[1];
				ray->doors_v[ray->num_doors_v][2] = ray->res_rc_v_3D[2];
				ray->doors_v[ray->num_doors_v][3] = distance(ray->res_rc_v_3D[0], ray->res_rc_v_3D[1], ray->game->player.pos[0], ray->game->player.pos[1]);
				ray->doors_v[ray->num_doors_v][4] = ray->res_rc_v_3D[4];
				ray->doors_v[ray->num_doors_v][5] = ray->res_rc_v_3D[5];
				ray->doors_v[ray->num_doors_v][6] = ray->res_rc_v_3D[6];
			}
		}
		range++;
		ray->res_rc_v_3D[1] += dir_y / fabs(dir_x) * B_SIZE;
		ray->res_rc_v_3D[0] += ((dir_x > 0) * 2 - 1) * B_SIZE;
		ray->res_rc_v_3D[2] += dir_z / fabs(dir_x) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

void	raycast_3D(t_raycast *ray)
{
	ray->num_doors_h = -1;
	ray->res_rc_h_3D[3] = raycast_h_3D(ray);
	ray->num_doors_v = -1;
	ray->res_rc_v_3D[3] = raycast_v_3D(ray);
	if (ray->res_rc_h_3D[3] < ray->res_rc_v_3D[3])
		ray->res_rc_3D = ray->res_rc_h_3D;
	else
		ray->res_rc_3D = ray->res_rc_v_3D;
}