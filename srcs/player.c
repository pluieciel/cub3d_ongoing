#include "cub3d.h"

static void	player_jump(t_data *game)
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

static void	update_player_state(t_data *game)
{
	if (game->key.shift)
		game->player.speed = SPEED * 2;
	else if (!game->key.shift)
		game->player.speed = SPEED;
	if (!game->key.space && game->key.ctrl)
		game->player.z = -10;
	else if (!game->key.space && !game->key.ctrl)
		game->player.z = 0;
	if (game->key.space)
		player_jump(game);
}

void	update_player(t_data *game)
{
	float		dir_x;
	float		dir_y;
	t_point3d	dir3d;

	dir_x = game->player.dir_x;
	dir_y = game->player.dir_y;
	dir3d.x = game->player.dir3d.x;
	dir3d.y = game->player.dir3d.y;
	move_player(game, dir_x, dir_y);
	rotate_player(game, dir_x, dir_y, &dir3d);
	update_player_state(game);
}
