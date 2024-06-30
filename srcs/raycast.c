#include "cub3D.h"

float	raycast_h(t_data *game, float x, float y)
{
	float	dir_x;
	float	dir_y;
	int		range;

	range = 0;
	dir_x = game->player.dir[0] * DIS_P_S + x;
	dir_y = game->player.dir[1] * DIS_P_S + y;
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
		&& game->map[(int)round(game->res_rc_h[1]) / B_SIZE - (dir_y < 0)][(int)round(game->res_rc_h[0]) / B_SIZE] == 1)
			return distance(game->res_rc_h[0], game->res_rc_h[1], game->player.pos[0], game->player.pos[1])
			* DIS_P_S / sqrt(dir_x * dir_x + dir_y * dir_y);
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
	dir_x = game->player.dir[0] * DIS_P_S + x;
	dir_y = game->player.dir[1] * DIS_P_S + y;
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
		&& game->map[(int)round(game->res_rc_v[1]) / B_SIZE][(int)round(game->res_rc_v[0]) / B_SIZE - (dir_x < 0)] == 1)
			return distance(game->res_rc_v[0], game->res_rc_v[1], game->player.pos[0], game->player.pos[1])
			* DIS_P_S / sqrt(dir_x * dir_x + dir_y * dir_y);
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