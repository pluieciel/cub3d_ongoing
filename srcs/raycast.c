#include "cub3D.h"

float	raycast_h(t_data *game, float x, float y)
{
	float	dir_x;
	float	dir_y;
	int		range;

	range = 0;
	dir_x = game->player.dir[0] * game->dis_p_s + x;
	dir_y = game->player.dir[1] * game->dis_p_s + y;
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
		if (dir_y != 0
		&& game->res_rc_h[1] / B_SIZE > 0 && game->res_rc_h[1] / B_SIZE < game->map_h
		&& game->map[(int)game->res_rc_h[1] / B_SIZE - (dir_y < 0)][(int)game->res_rc_h[0] / B_SIZE] == 1)
			return distance(game->res_rc_h[0], game->res_rc_h[1], game->player.pos[0], game->player.pos[1])
			* game->dis_p_s / sqrt(dir_x * dir_x + dir_y * dir_y);
		range++;
		game->res_rc_h[0] += dir_x / fabs(dir_y) * B_SIZE;
		game->res_rc_h[1] += ((dir_y > 0) * 2 - 1) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

float	raycast_v(t_data *game, float x, float y)
{
	float	dir_x;
	float	dir_y;
	int		range;

	range = 0;
	dir_x = game->player.dir[0] * game->dis_p_s + x;
	dir_y = game->player.dir[1] * game->dis_p_s + y;
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
		if (dir_x != 0
		&& game->res_rc_v[0] / B_SIZE > 0 && game->res_rc_v[0] / B_SIZE < game->map_w
		&& game->map[(int)game->res_rc_v[1] / B_SIZE][(int)game->res_rc_v[0] / B_SIZE - (dir_x < 0)] == 1)
			return distance(game->res_rc_v[0], game->res_rc_v[1], game->player.pos[0], game->player.pos[1])
			* game->dis_p_s / sqrt(dir_x * dir_x + dir_y * dir_y);
		range++;
		game->res_rc_v[1] += dir_y / fabs(dir_x) * B_SIZE;
		game->res_rc_v[0] += ((dir_x > 0) * 2 - 1) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

void	raycast(t_data *game, float x, float y)
{
	game->res_rc_h[2] = raycast_h(game, x, y);
	game->res_rc_v[2] = raycast_v(game, x, y);
	if (game->res_rc_h[2] < game->res_rc_v[2])
		game->res_rc = game->res_rc_h;
	else
		game->res_rc = game->res_rc_v;
}

float	raycast_h_3D(t_data *game, float x, float y, float z)
{
	float	dir_x;
	float	dir_y;
	float	dir_z;
	int		range;
	int		type;

	range = 0;
	dir_x = game->player.dir3D.x * game->dis_p_s + x;
	dir_y = game->player.dir3D.y * game->dis_p_s + y;
	dir_z = game->player.dir3D.z * game->dis_p_s + z;
	if (dir_y < 0)
	{
		game->res_rc_h_3D[1] = game->player.pos[1] - game->player.pos[1] % B_SIZE;
		game->res_rc_h_3D[0] = game->player.pos[0] - (game->player.pos[1] % B_SIZE) * dir_x / dir_y;
		game->res_rc_h_3D[2] = (game->player.pos[1] % B_SIZE) * dir_z / -dir_y;
		game->res_rc_h_3D[4] = 1;
	}
	else if (dir_y > 0)
	{
		game->res_rc_h_3D[1] = game->player.pos[1] + B_SIZE - game->player.pos[1] % B_SIZE;
		game->res_rc_h_3D[0] = game->player.pos[0] + (B_SIZE - game->player.pos[1] % B_SIZE) * dir_x / dir_y;
		game->res_rc_h_3D[2] = (B_SIZE - game->player.pos[1] % B_SIZE) * dir_z / dir_y;
		game->res_rc_h_3D[4] = -1;
	}
	else
	{
		range = RAYCAST_RANGE;
		game->res_rc_h_3D[0] = game->player.pos[0];
		game->res_rc_h_3D[1] = game->player.pos[1];
		game->res_rc_h_3D[4] = 0;
	}
	while (range < RAYCAST_RANGE
	&& game->res_rc_h_3D[0] / B_SIZE > 0 && game->res_rc_h_3D[0] / B_SIZE < game->map_w
	&& game->res_rc_h_3D[2] <= B_SIZE / 2 && game->res_rc_h_3D[2] >= -B_SIZE / 2)
	{
		if (dir_y != 0
		&& game->res_rc_h_3D[1] / B_SIZE > 0 && game->res_rc_h_3D[1] / B_SIZE < game->map_h)
		{
			type = game->map[(int)game->res_rc_h_3D[1] / B_SIZE - (dir_y < 0)][(int)game->res_rc_h_3D[0] / B_SIZE];
			if (type == 1)
				return distance(game->res_rc_h_3D[0], game->res_rc_h_3D[1], game->player.pos[0], game->player.pos[1]);
			else if (type == 2)
			{
				game->num_doors_h++;
				game->doors_h[game->num_doors_h][0] = game->res_rc_h_3D[0];
				game->doors_h[game->num_doors_h][1] = game->res_rc_h_3D[1];
				game->doors_h[game->num_doors_h][2] = game->res_rc_h_3D[2];
				game->doors_h[game->num_doors_h][3] = distance(game->res_rc_h_3D[0], game->res_rc_h_3D[1], game->player.pos[0], game->player.pos[1]);
				game->doors_h[game->num_doors_h][4] = game->res_rc_h_3D[4];
			}
		}
		range++;
		game->res_rc_h_3D[0] += dir_x / fabs(dir_y) * B_SIZE;
		game->res_rc_h_3D[1] += ((dir_y > 0) * 2 - 1) * B_SIZE;
		game->res_rc_h_3D[2] += dir_z / fabs(dir_y) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

float	raycast_v_3D(t_data *game, float x, float y, float z)
{
	float	dir_x;
	float	dir_y;
	float	dir_z;
	int		range;
	int		type;

	range = 0;
	dir_x = game->player.dir3D.x * game->dis_p_s + x;
	dir_y = game->player.dir3D.y * game->dis_p_s + y;
	dir_z = game->player.dir3D.z * game->dis_p_s + z;
	if (dir_x < 0)
	{
		game->res_rc_v_3D[0] = game->player.pos[0] - game->player.pos[0] % B_SIZE;
		game->res_rc_v_3D[1] = game->player.pos[1] - (game->player.pos[0] % B_SIZE) * dir_y / dir_x;
		game->res_rc_v_3D[2] = (game->player.pos[0] % B_SIZE) * dir_z / -dir_x;
		game->res_rc_v_3D[4] = -1;
	}
	else if (dir_x > 0)
	{
		game->res_rc_v_3D[0] = game->player.pos[0] + B_SIZE - game->player.pos[0] % B_SIZE;
		game->res_rc_v_3D[1] = game->player.pos[1] + (B_SIZE - game->player.pos[0] % B_SIZE) * dir_y / dir_x;
		game->res_rc_v_3D[2] = (B_SIZE - game->player.pos[0] % B_SIZE) * dir_z / dir_x;
		game->res_rc_v_3D[4] = 1;
	}
	else
	{
		range = RAYCAST_RANGE;
		game->res_rc_v_3D[0] = game->player.pos[0];
		game->res_rc_v_3D[1] = game->player.pos[1];
		game->res_rc_v_3D[4] = 0;
	}
	while (range < RAYCAST_RANGE
	&& game->res_rc_v_3D[1] / B_SIZE > 0 && game->res_rc_v_3D[1] / B_SIZE < game->map_h
	&& game->res_rc_v_3D[2] <= B_SIZE / 2 && game->res_rc_v_3D[2] >= -B_SIZE / 2)
	{
		if (dir_x != 0
		&& game->res_rc_v_3D[0] / B_SIZE > 0 && game->res_rc_v_3D[0] / B_SIZE < game->map_w)
		{
			type = game->map[(int)game->res_rc_v_3D[1] / B_SIZE][(int)game->res_rc_v_3D[0] / B_SIZE - (dir_x < 0)];
			if (type == 1)
				return distance(game->res_rc_v_3D[0], game->res_rc_v_3D[1], game->player.pos[0], game->player.pos[1]);
			else if (type == 2)
			{
				game->num_doors_v++;
				game->doors_v[game->num_doors_v][0] = game->res_rc_v_3D[0];
				game->doors_v[game->num_doors_v][1] = game->res_rc_v_3D[1];
				game->doors_v[game->num_doors_v][2] = game->res_rc_v_3D[2];
				game->doors_v[game->num_doors_v][3] = distance(game->res_rc_v_3D[0], game->res_rc_v_3D[1], game->player.pos[0], game->player.pos[1]);
				game->doors_v[game->num_doors_v][4] = game->res_rc_v_3D[4];
			}
		}
		range++;
		game->res_rc_v_3D[1] += dir_y / fabs(dir_x) * B_SIZE;
		game->res_rc_v_3D[0] += ((dir_x > 0) * 2 - 1) * B_SIZE;
		game->res_rc_v_3D[2] += dir_z / fabs(dir_x) * B_SIZE;
	}
	return (float)(RAYCAST_RANGE + 1) * B_SIZE;
}

void	raycast_3D(t_data *game, float x, float y, float z)
{
	game->num_doors_h = -1;
	game->res_rc_h_3D[3] = raycast_h_3D(game, x, y, z);
	game->num_doors_v = -1;
	game->res_rc_v_3D[3] = raycast_v_3D(game, x, y, z);
	if (game->res_rc_h_3D[3] < game->res_rc_v_3D[3])
		game->res_rc_3D = game->res_rc_h_3D;
	else
		game->res_rc_3D = game->res_rc_v_3D;
}