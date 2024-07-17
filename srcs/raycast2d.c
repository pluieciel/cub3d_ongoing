#include "cub3d.h"

float	raycast_h2(t_data *g, float x, float y, int type)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE && g->res_rc_h.x / B_SIZE > 0
		&& g->res_rc_h.x / B_SIZE < g->map_w)
	{
		g->res_rc_h.map_y = (int)g->res_rc_h.y / B_SIZE - (y < 0);
		g->res_rc_h.map_x = (int)g->res_rc_h.x / B_SIZE;
		if (y != 0
			&& g->res_rc_h.map_y >= 0 && g->res_rc_h.map_y < g->map_h
			&& (g->map[(int)g->res_rc_h.map_y][(int)g->res_rc_h.map_x] == 1
			|| g->map[(int)g->res_rc_h.map_y][(int)g->res_rc_h.map_x] == 2
			|| (type && g->map[(int)g->res_rc_h.map_y][(int)g->res_rc_h.map_x] == 3)))
			return (distance(g->res_rc_h.x, g->res_rc_h.y,
					g->player.x, g->player.y));
		range++;
		g->res_rc_h.x += x / fabs(y) * B_SIZE;
		g->res_rc_h.y += ((y > 0) * 2 - 1) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_h(t_data *g, float x, float y, int type)
{
	if (y < 0)
	{
		g->res_rc_h.y = g->player.y - g->player.y % B_SIZE;
		g->res_rc_h.x = g->player.x - (g->player.y % B_SIZE) * x / y;
		g->res_rc_h.dir = -1;
	}
	else if (y > 0)
	{
		g->res_rc_h.y = g->player.y + B_SIZE - g->player.y % B_SIZE;
		g->res_rc_h.x = g->player.x
			+ (B_SIZE - g->player.y % B_SIZE) * x / y;
		g->res_rc_h.dir = 1;
	}
	else
	{
		g->res_rc_h.x = g->player.x;
		g->res_rc_h.y = g->player.y;
		g->res_rc_h.dir = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_h2(g, x, y, type));
}

float	raycast_v2(t_data *g, float x, float y, int type)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE && g->res_rc_v.y / B_SIZE > 0
		&& g->res_rc_v.y / B_SIZE < g->map_h)
	{
		g->res_rc_v.map_y = (int)g->res_rc_v.y / B_SIZE;
		g->res_rc_v.map_x = (int)g->res_rc_v.x / B_SIZE - (x < 0);
		if (x != 0
			&& g->res_rc_v.map_x >= 0 && g->res_rc_v.map_x < g->map_w
			&& (g->map[(int)g->res_rc_v.map_y][(int)g->res_rc_v.map_x] == 1
			|| g->map[(int)g->res_rc_v.map_y][(int)g->res_rc_v.map_x] == 2
			|| (type && g->map[(int)g->res_rc_v.map_y][(int)g->res_rc_v.map_x] == 3)))
			return (distance(g->res_rc_v.x, g->res_rc_v.y,
					g->player.x, g->player.y));
		range++;
		g->res_rc_v.y += y / fabs(x) * B_SIZE;
		g->res_rc_v.x += ((x > 0) * 2 - 1) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_v(t_data *g, float x, float y, int type)
{
	if (x < 0)
	{
		g->res_rc_v.x = g->player.x - g->player.x % B_SIZE;
		g->res_rc_v.y = g->player.y - (g->player.x % B_SIZE) * y / x;
		g->res_rc_v.dir = -1;
	}
	else if (x > 0)
	{
		g->res_rc_v.x = g->player.x + B_SIZE - g->player.x % B_SIZE;
		g->res_rc_v.y = g->player.y
			+ (B_SIZE - g->player.x % B_SIZE) * y / x;
		g->res_rc_v.dir = 1;
	}
	else
	{
		g->res_rc_v.x = g->player.x;
		g->res_rc_v.y = g->player.y;
		g->res_rc_v.dir = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_v2(g, x, y, type));
}

void	raycast(t_data *game, float x, float y, int type)
{
	game->res_rc_h.dis = raycast_h(game, x, y, type);
	game->res_rc_v.dis = raycast_v(game, x, y, type);
	if (game->res_rc_h.dis < game->res_rc_v.dis)
		game->res_rc = &game->res_rc_h;
	else
		game->res_rc = &game->res_rc_v;
}
