#include "cub3D.h"

float	raycast_h_3D(t_raycast *ray)
{
	float	dir_x;
	float	dir_y;
	float	dir_z;
	int		range;
	int		type;

	range = 0;
	dir_x = ray->game->player.dir3d.x * ray->game->dis_p_s + ray->temp[0];
	dir_y = ray->game->player.dir3d.y * ray->game->dis_p_s + ray->temp[1];
	dir_z = ray->game->player.dir3d.z * ray->game->dis_p_s + ray->temp[2];
	if (dir_y < 0)
	{
		ray->res_rc_h_3d[1] = ray->game->player.pos[1] - ray->game->player.pos[1] % B_SIZE;
		ray->res_rc_h_3d[0] = ray->game->player.pos[0] - (ray->game->player.pos[1] % B_SIZE) * dir_x / dir_y;
		ray->res_rc_h_3d[2] = (ray->game->player.pos[1] % B_SIZE) * dir_z / -dir_y;
		ray->res_rc_h_3d[4] = 1;
	}
	else if (dir_y > 0)
	{
		ray->res_rc_h_3d[1] = ray->game->player.pos[1] + B_SIZE - ray->game->player.pos[1] % B_SIZE;
		ray->res_rc_h_3d[0] = ray->game->player.pos[0] + (B_SIZE - ray->game->player.pos[1] % B_SIZE) * dir_x / dir_y;
		ray->res_rc_h_3d[2] = (B_SIZE - ray->game->player.pos[1] % B_SIZE) * dir_z / dir_y;
		ray->res_rc_h_3d[4] = -1;
	}
	else
	{
		range = RAYCAST_RANGE;
		ray->res_rc_h_3d[0] = ray->game->player.pos[0];
		ray->res_rc_h_3d[1] = ray->game->player.pos[1];
		ray->res_rc_h_3d[4] = 0;
	}
	while (range < RAYCAST_RANGE
	&& ray->res_rc_h_3d[0] / B_SIZE > 0 && ray->res_rc_h_3d[0] / B_SIZE < ray->game->map_w
	&& ray->res_rc_h_3d[2] <= B_SIZE / 2 && ray->res_rc_h_3d[2] >= -B_SIZE / 2)
	{
		ray->res_rc_h_3d[5] = (int)ray->res_rc_h_3d[0] / B_SIZE;
		ray->res_rc_h_3d[6] = (int)ray->res_rc_h_3d[1] / B_SIZE - (dir_y < 0);
		if (dir_y != 0
		&& ray->res_rc_h_3d[6] >= 0 && ray->res_rc_h_3d[6] < ray->game->map_h)
		{
			type = ray->game->map[(int)ray->res_rc_h_3d[6]][(int)ray->res_rc_h_3d[5]];
			if (type == 1)
				return distance(ray->res_rc_h_3d[0], ray->res_rc_h_3d[1], ray->game->player.pos[0], ray->game->player.pos[1]);
			else if (type >= 2)
			{
				ray->num_doors_h++;
				ray->doors_h[ray->num_doors_h][0] = ray->res_rc_h_3d[0];
				ray->doors_h[ray->num_doors_h][1] = ray->res_rc_h_3d[1];
				ray->doors_h[ray->num_doors_h][2] = ray->res_rc_h_3d[2];
				ray->doors_h[ray->num_doors_h][3] = distance(ray->res_rc_h_3d[0], ray->res_rc_h_3d[1], ray->game->player.pos[0], ray->game->player.pos[1]);
				ray->doors_h[ray->num_doors_h][4] = ray->res_rc_h_3d[4];
				ray->doors_h[ray->num_doors_h][5] = ray->res_rc_h_3d[5];
				ray->doors_h[ray->num_doors_h][6] = ray->res_rc_h_3d[6];
			}
		}
		range++;
		ray->res_rc_h_3d[0] += dir_x / fabs(dir_y) * B_SIZE;
		ray->res_rc_h_3d[1] += ((dir_y > 0) * 2 - 1) * B_SIZE;
		ray->res_rc_h_3d[2] += dir_z / fabs(dir_y) * B_SIZE;
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
	dir_x = ray->game->player.dir3d.x * ray->game->dis_p_s + ray->temp[0];
	dir_y = ray->game->player.dir3d.y * ray->game->dis_p_s + ray->temp[1];
	dir_z = ray->game->player.dir3d.z * ray->game->dis_p_s + ray->temp[2];
	if (dir_x < 0)
	{
		ray->res_rc_v_3d[0] = ray->game->player.pos[0] - ray->game->player.pos[0] % B_SIZE;
		ray->res_rc_v_3d[1] = ray->game->player.pos[1] - (ray->game->player.pos[0] % B_SIZE) * dir_y / dir_x;
		ray->res_rc_v_3d[2] = (ray->game->player.pos[0] % B_SIZE) * dir_z / -dir_x;
		ray->res_rc_v_3d[4] = -1;
	}
	else if (dir_x > 0)
	{
		ray->res_rc_v_3d[0] = ray->game->player.pos[0] + B_SIZE - ray->game->player.pos[0] % B_SIZE;
		ray->res_rc_v_3d[1] = ray->game->player.pos[1] + (B_SIZE - ray->game->player.pos[0] % B_SIZE) * dir_y / dir_x;
		ray->res_rc_v_3d[2] = (B_SIZE - ray->game->player.pos[0] % B_SIZE) * dir_z / dir_x;
		ray->res_rc_v_3d[4] = 1;
	}
	else
	{
		range = RAYCAST_RANGE;
		ray->res_rc_v_3d[0] = ray->game->player.pos[0];
		ray->res_rc_v_3d[1] = ray->game->player.pos[1];
		ray->res_rc_v_3d[4] = 0;
	}
	while (range < RAYCAST_RANGE
	&& ray->res_rc_v_3d[1] / B_SIZE > 0 && ray->res_rc_v_3d[1] / B_SIZE < ray->game->map_h
	&& ray->res_rc_v_3d[2] <= B_SIZE / 2 && ray->res_rc_v_3d[2] >= -B_SIZE / 2)
	{
		ray->res_rc_v_3d[5] = (int)ray->res_rc_v_3d[0] / B_SIZE - (dir_x < 0);
		ray->res_rc_v_3d[6] = (int)ray->res_rc_v_3d[1] / B_SIZE;
		if (dir_x != 0
		&& ray->res_rc_v_3d[5] >= 0 && ray->res_rc_v_3d[5] < ray->game->map_w)
		{
			type = ray->game->map[(int)ray->res_rc_v_3d[6]][(int)ray->res_rc_v_3d[5]];
			if (type == 1)
				return distance(ray->res_rc_v_3d[0], ray->res_rc_v_3d[1], ray->game->player.pos[0], ray->game->player.pos[1]);
			else if (type >= 2)
			{
				ray->num_doors_v++;
				ray->doors_v[ray->num_doors_v][0] = ray->res_rc_v_3d[0];
				ray->doors_v[ray->num_doors_v][1] = ray->res_rc_v_3d[1];
				ray->doors_v[ray->num_doors_v][2] = ray->res_rc_v_3d[2];
				ray->doors_v[ray->num_doors_v][3] = distance(ray->res_rc_v_3d[0], ray->res_rc_v_3d[1], ray->game->player.pos[0], ray->game->player.pos[1]);
				ray->doors_v[ray->num_doors_v][4] = ray->res_rc_v_3d[4];
				ray->doors_v[ray->num_doors_v][5] = ray->res_rc_v_3d[5];
				ray->doors_v[ray->num_doors_v][6] = ray->res_rc_v_3d[6];
			}
		}
		range++;
		ray->res_rc_v_3d[1] += dir_y / fabs(dir_x) * B_SIZE;
		ray->res_rc_v_3d[0] += ((dir_x > 0) * 2 - 1) * B_SIZE;
		ray->res_rc_v_3d[2] += dir_z / fabs(dir_x) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

void	raycast_3D(t_raycast *ray)
{
	ray->num_doors_h = -1;
	ray->res_rc_h_3d[3] = raycast_h_3D(ray);
	ray->num_doors_v = -1;
	ray->res_rc_v_3d[3] = raycast_v_3D(ray);
	if (ray->res_rc_h_3d[3] < ray->res_rc_v_3d[3])
		ray->res_rc_3d = ray->res_rc_h_3d;
	else
		ray->res_rc_3d = ray->res_rc_v_3d;
}