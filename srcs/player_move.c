#include "cub3d.h"

static void	move_forward(t_data *game, float dir_x, float dir_y, float scale)
{
	check_collisions(game, game->player.dir_x, game->player.dir_y, scale);
	if (!game->coll_wall_v)
		game->player.x += round(dir_x * game->player.speed);
	if (!game->coll_wall_h)
		game->player.y += round(dir_y * game->player.speed);
}

static void	move_backward(t_data *game, float dir_x, float dir_y, float scale)
{
	check_collisions(game, -game->player.dir_x, -game->player.dir_y, -scale);
	if (!game->coll_wall_v)
		game->player.x -= round(dir_x * game->player.speed);
	if (!game->coll_wall_h)
		game->player.y -= round(dir_y * game->player.speed);
}

static void	move_left(t_data *game, float dir_x, float dir_y, float scale)
{
	check_collisions(game, game->player.dir_y, -game->player.dir_x, scale);
	if (!game->coll_wall_v)
		game->player.x += round(dir_y * game->player.speed);
	if (!game->coll_wall_h)
		game->player.y -= round(dir_x * game->player.speed);
}

static void	move_right(t_data *game, float dir_x, float dir_y, float scale)
{
	check_collisions(game, -game->player.dir_y, game->player.dir_x, -scale);
	if (!game->coll_wall_v)
		game->player.x -= round(dir_y * game->player.speed);
	if (!game->coll_wall_h)
		game->player.y += round(dir_x * game->player.speed);
}

void	move_player(t_data *game, float dir_x, float dir_y)
{
	float	scale;

	game->coll_wall_h = 0;
	game->coll_wall_v = 0;
	scale = sqrt(2) / 2;
	if (game->key.w)
		move_forward(game, dir_x, dir_y, scale);
	else if (game->key.s)
		move_backward(game, dir_x, dir_y, scale);
	if (game->key.a)
		move_left(game, dir_x, dir_y, scale);
	else if (game->key.d)
		move_right(game, dir_x, dir_y, scale);
}
