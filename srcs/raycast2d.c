#include "cub3d.h"

float	raycast_h2(t_data *g, float x, float y, int type)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE && g->res_rc_h[0] / B_SIZE > 0
		&& g->res_rc_h[0] / B_SIZE < g->map_w)
	{
		g->res_rc_h[5] = (int)g->res_rc_h[1] / B_SIZE - (y < 0);
		g->res_rc_h[4] = (int)g->res_rc_h[0] / B_SIZE;
		if (y != 0
			&& g->res_rc_h[5] >= 0 && g->res_rc_h[5] < g->map_h
			&& (g->map[(int)g->res_rc_h[5]][(int)g->res_rc_h[4]] == 1
			|| g->map[(int)g->res_rc_h[5]][(int)g->res_rc_h[4]] == 2
			|| (type && g->map[(int)g->res_rc_h[5]][(int)g->res_rc_h[4]] == 3)))
			return (distance(g->res_rc_h[0], g->res_rc_h[1],
					g->player.pos[0], g->player.pos[1]));
		range++;
		g->res_rc_h[0] += x / fabs(y) * B_SIZE;
		g->res_rc_h[1] += ((y > 0) * 2 - 1) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_h(t_data *g, float x, float y, int type)
{
	if (y < 0)
	{
		g->res_rc_h[1] = g->player.pos[1] - g->player.pos[1] % B_SIZE;
		g->res_rc_h[0] = g->player.pos[0] - (g->player.pos[1] % B_SIZE) * x / y;
		g->res_rc_h[3] = -1;
	}
	else if (y > 0)
	{
		g->res_rc_h[1] = g->player.pos[1] + B_SIZE - g->player.pos[1] % B_SIZE;
		g->res_rc_h[0] = g->player.pos[0]
			+ (B_SIZE - g->player.pos[1] % B_SIZE) * x / y;
		g->res_rc_h[3] = 1;
	}
	else
	{
		g->res_rc_h[0] = g->player.pos[0];
		g->res_rc_h[1] = g->player.pos[1];
		g->res_rc_h[3] = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_h2(g, x, y, type));
}

float	raycast_v2(t_data *g, float x, float y, int type)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE && g->res_rc_v[1] / B_SIZE > 0
		&& g->res_rc_v[1] / B_SIZE < g->map_h)
	{
		g->res_rc_v[5] = (int)g->res_rc_v[1] / B_SIZE;
		g->res_rc_v[4] = (int)g->res_rc_v[0] / B_SIZE - (x < 0);
		if (x != 0
			&& g->res_rc_v[4] >= 0 && g->res_rc_v[4] < g->map_w
			&& (g->map[(int)g->res_rc_v[5]][(int)g->res_rc_v[4]] == 1
			|| g->map[(int)g->res_rc_v[5]][(int)g->res_rc_v[4]] == 2
			|| (type && g->map[(int)g->res_rc_v[5]][(int)g->res_rc_v[4]] == 3)))
			return (distance(g->res_rc_v[0], g->res_rc_v[1],
					g->player.pos[0], g->player.pos[1]));
		range++;
		g->res_rc_v[1] += y / fabs(x) * B_SIZE;
		g->res_rc_v[0] += ((x > 0) * 2 - 1) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_v(t_data *g, float x, float y, int type)
{
	if (x < 0)
	{
		g->res_rc_v[0] = g->player.pos[0] - g->player.pos[0] % B_SIZE;
		g->res_rc_v[1] = g->player.pos[1] - (g->player.pos[0] % B_SIZE) * y / x;
		g->res_rc_v[3] = -1;
	}
	else if (x > 0)
	{
		g->res_rc_v[0] = g->player.pos[0] + B_SIZE - g->player.pos[0] % B_SIZE;
		g->res_rc_v[1] = g->player.pos[1]
			+ (B_SIZE - g->player.pos[0] % B_SIZE) * y / x;
		g->res_rc_v[3] = 1;
	}
	else
	{
		g->res_rc_v[0] = g->player.pos[0];
		g->res_rc_v[1] = g->player.pos[1];
		g->res_rc_v[3] = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_v2(g, x, y, type));
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
