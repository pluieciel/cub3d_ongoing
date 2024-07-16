#include "../includes/cub3d.h"

static void	handle_handgun_idle_state(t_data *game)
{
	if (game->handgun.equiped)
	{
		render_image(game, (t_image *)game->handgun.shoot.head->content, 0, 0);
		collision(game, game->player.dir[0], game->player.dir[1], COLL_DIS);
		if (game->left_click)
			game->handgun.state = HANDGUN_SHOOT;
		else if (game->key.two || game->key.one)
			game->handgun.state = HANDGUN_HOLSTER;
	}
	else if (game->key.two)
		game->handgun.state = HANDGUN_DRAW;
}

static void	handle_handgun_completed(t_data *game)
{
	if (game->key.one)
	{
		game->handgun.state = HANDGUN_NONE;
		game->crowbar.state = CROWBAR_DRAW;
	}
	if (game->handgun.state != HANDGUN_NONE)
	{
		game->handgun.state = HANDGUN_IDLE;
		game->key.two = 0;
		game->key.one = 0;
	}
}

void	update_handgun_state(t_data *game)
{
	int	*completed;

	completed = &game->handgun.completed;
	*completed = 0;
	if (game->handgun.state == HANDGUN_IDLE)
		handle_handgun_idle_state(game);
	else if (game->handgun.state == HANDGUN_DRAW)
	{
		*completed = handle_animation_state(game, &game->handgun.draw, FPS);
		if (*completed)
			game->handgun.equiped = 1;
	}
	else if (game->handgun.state == HANDGUN_SHOOT)
		*completed = handle_animation_state(game, &game->handgun.shoot, FPS
				/ 2);
	else if (game->handgun.state == HANDGUN_HOLSTER)
	{
		*completed = handle_animation_state(game, &game->handgun.holster, FPS);
		if (*completed)
			game->handgun.equiped = 0;
	}
	if (*completed)
		handle_handgun_completed(game);
}
