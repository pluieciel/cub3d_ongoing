#include "cub3D.h"

float raycast_h(t_data *game, float x, float y)
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
		game->res_rc_h[0] = game->player.pos[0] - (int)round((game->player.pos[1] % B_SIZE) * dir_x / dir_y);
	}
	else if (dir_y > 0)
	{
		game->res_rc_h[1] = game->player.pos[1] +  B_SIZE - game->player.pos[1] % B_SIZE;
		game->res_rc_h[0] = game->player.pos[0] + (int)round((B_SIZE - game->player.pos[1] % B_SIZE) * dir_x / dir_y);
	}
	else
		range = RAYCAST_RANGE;
	while (range < RAYCAST_RANGE)
	{
		if (dir_y > 0 && game->res_rc_h[1] / B_SIZE >= 0 && game->res_rc_h[1] / B_SIZE < game->map_h
		&& game->res_rc_h[0] / B_SIZE >= 0 && game->res_rc_h[0] / B_SIZE < game->map_w
		&& game->map[game->res_rc_h[1] / B_SIZE][game->res_rc_h[0] / B_SIZE] == 1)
			return distance(game->res_rc_h[0], game->res_rc_h[1], game->player.pos[0], game->player.pos[1]);
		else if (dir_y < 0 && game->res_rc_h[1] / B_SIZE >= 0 && game->res_rc_h[1] / B_SIZE < game->map_h
		&& game->res_rc_h[0] / B_SIZE >= 0 && game->res_rc_h[0] / B_SIZE < game->map_w
		&& game->map[game->res_rc_h[1] / B_SIZE - 1][game->res_rc_h[0] / B_SIZE] == 1)
			return distance(game->res_rc_h[0], game->res_rc_h[1], game->player.pos[0], game->player.pos[1]);
		range++;
		game->res_rc_h[0] += ((dir_y > 0) * 2 - 1) * dir_x / dir_y * B_SIZE;
		game->res_rc_h[1] += ((dir_y > 0) * 2 - 1) * B_SIZE;
	}
	return 100000.0f;
}