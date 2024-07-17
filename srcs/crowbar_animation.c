#include "../includes/cub3d.h"

static void	handle_crowbar_idle_state(t_data *game)
{
	if (game->crowbar.equiped)
	{
		render_image(game, (t_image *)game->crowbar.attack.head->content, 0, 0);
		check_collision(game, game->player.dir_x, game->player.dir_y, COLL_DIS);
		if (game->left_click && !game->coll_wall_h && !game->coll_wall_v)
			game->crowbar.state = CROWBAR_ATTACK;
		else if (game->left_click && (game->coll_wall_h || game->coll_wall_v))
			game->crowbar.state = CROWBAR_ATTACK_HIT;
		else if (game->key.one || game->key.two)
			game->crowbar.state = CROWBAR_HOLSTER;
	}
	else if (game->key.one)
		game->crowbar.state = CROWBAR_DRAW;
}

static void	handle_crowbar_completed(t_data *game)
{
	if (game->key.two)
	{
		game->crowbar.state = CROWBAR_NONE;
		game->handgun.state = HANDGUN_DRAW;
	}
	if (game->crowbar.state != CROWBAR_NONE)
	{
		game->crowbar.state = CROWBAR_IDLE;
		game->key.two = 0;
		game->key.one = 0;
	}
}

void	update_crowbar_state(t_data *game)
{
	int	*completed;

	completed = &game->crowbar.completed;
	*completed = 0;
	if (game->crowbar.state == CROWBAR_IDLE)
		handle_crowbar_idle_state(game);
	else if (game->crowbar.state == CROWBAR_DRAW)
	{
		*completed = handle_animation_state(game, &game->crowbar.draw, FPS);
		if (*completed)
			game->crowbar.equiped = 1;
	}
	else if (game->crowbar.state == CROWBAR_ATTACK)
		*completed = handle_animation_state(game, &game->crowbar.attack, FPS);
	else if (game->crowbar.state == CROWBAR_ATTACK_HIT)
		*completed = handle_animation_state(game, &game->crowbar.attack_hit,
				FPS);
	else if (game->crowbar.state == CROWBAR_HOLSTER)
	{
		*completed = handle_animation_state(game, &game->crowbar.holster, FPS);
		if (*completed)
			game->crowbar.equiped = 0;
	}
	if (*completed)
		handle_crowbar_completed(game);
}
