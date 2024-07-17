#include "cub3d.h"

float	raycast_h2(t_data *g, float x, float y, int type)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE && g->rc_h.x / B_SIZE > 0
		&& g->rc_h.x / B_SIZE < g->map_w)
	{
		g->rc_h.map_y = (int)g->rc_h.y / B_SIZE - (y < 0);
		g->rc_h.map_x = (int)g->rc_h.x / B_SIZE;
		if (y != 0
			&& g->rc_h.map_y >= 0 && g->rc_h.map_y < g->map_h
			&& (g->map[(int)g->rc_h.map_y][(int)g->rc_h.map_x] == 1
			|| g->map[(int)g->rc_h.map_y][(int)g->rc_h.map_x] == 2
			|| (type && g->map[(int)g->rc_h.map_y][(int)g->rc_h.map_x] == 3)))
			return (distance(g->rc_h.x, g->rc_h.y,
					g->player.x, g->player.y));
		range++;
		g->rc_h.x += x / fabs(y) * B_SIZE;
		g->rc_h.y += ((y > 0) * 2 - 1) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_h(t_data *g, float x, float y, int type)
{
	if (y < 0)
	{
		g->rc_h.y = g->player.y - g->player.y % B_SIZE;
		g->rc_h.x = g->player.x - (g->player.y % B_SIZE) * x / y;
		g->rc_h.dir = -1;
	}
	else if (y > 0)
	{
		g->rc_h.y = g->player.y + B_SIZE - g->player.y % B_SIZE;
		g->rc_h.x = g->player.x
			+ (B_SIZE - g->player.y % B_SIZE) * x / y;
		g->rc_h.dir = 1;
	}
	else
	{
		g->rc_h.x = g->player.x;
		g->rc_h.y = g->player.y;
		g->rc_h.dir = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_h2(g, x, y, type));
}

float	raycast_v2(t_data *g, float x, float y, int type)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE && g->rc_v.y / B_SIZE > 0
		&& g->rc_v.y / B_SIZE < g->map_h)
	{
		g->rc_v.map_y = (int)g->rc_v.y / B_SIZE;
		g->rc_v.map_x = (int)g->rc_v.x / B_SIZE - (x < 0);
		if (x != 0
			&& g->rc_v.map_x >= 0 && g->rc_v.map_x < g->map_w
			&& (g->map[(int)g->rc_v.map_y][(int)g->rc_v.map_x] == 1
			|| g->map[(int)g->rc_v.map_y][(int)g->rc_v.map_x] == 2
			|| (type && g->map[(int)g->rc_v.map_y][(int)g->rc_v.map_x] == 3)))
			return (distance(g->rc_v.x, g->rc_v.y,
					g->player.x, g->player.y));
		range++;
		g->rc_v.y += y / fabs(x) * B_SIZE;
		g->rc_v.x += ((x > 0) * 2 - 1) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_v(t_data *g, float x, float y, int type)
{
	if (x < 0)
	{
		g->rc_v.x = g->player.x - g->player.x % B_SIZE;
		g->rc_v.y = g->player.y - (g->player.x % B_SIZE) * y / x;
		g->rc_v.dir = -1;
	}
	else if (x > 0)
	{
		g->rc_v.x = g->player.x + B_SIZE - g->player.x % B_SIZE;
		g->rc_v.y = g->player.y
			+ (B_SIZE - g->player.x % B_SIZE) * y / x;
		g->rc_v.dir = 1;
	}
	else
	{
		g->rc_v.x = g->player.x;
		g->rc_v.y = g->player.y;
		g->rc_v.dir = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_v2(g, x, y, type));
}

void	raycast(t_data *game, float x, float y, int type)
{
	game->rc_h.dis = raycast_h(game, x, y, type);
	game->rc_v.dis = raycast_v(game, x, y, type);
	if (game->rc_h.dis < game->rc_v.dis)
		game->rc = &game->rc_h;
	else
		game->rc = &game->rc_v;
}
