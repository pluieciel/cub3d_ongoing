/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crowbar_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:07:56 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/19 23:12:17 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_crowbar_idle_state(t_data *game)
{
	if (game->crowbar.equiped)
	{
		render_image(game, (t_image *)game->crowbar.attack.head->content, 0, 0);
		check_collision(game, game->player.dir_x, game->player.dir_y, COLL_DIS);
		if (game->left_click && !game->coll_wall_h && !game->coll_wall_v)
			game->crowbar.state = ATTACK;
		else if (game->left_click && (game->coll_wall_h || game->coll_wall_v))
			game->crowbar.state = ATTACK_HIT;
		else if (game->key.two || game->key.three)
			game->crowbar.state = HOLSTER;
	}
	else if (game->key.one)
		game->crowbar.state = DRAW;
}

static void	handle_crowbar_completed(t_data *game)
{
	if (game->key.two)
	{
		game->crowbar.state = NONE;
		game->handgun.state = DRAW;
	}
	else if (game->key.three)
	{
		game->crowbar.state = NONE;
		game->shotgun.state = DRAW;
	}
	if (game->crowbar.state != NONE)
	{
		game->crowbar.state = IDLE;
		game->key.two = 0;
		game->key.one = 0;
		game->key.three = 0;
	}
}

void	update_crowbar_state(t_data *game)
{
	bool	*completed;

	completed = &game->crowbar.completed;
	*completed = 0;
	if (game->crowbar.state == IDLE)
		handle_crowbar_idle_state(game);
	else if (game->crowbar.state == DRAW)
	{
		*completed = handle_animation_state(game, &game->crowbar.draw, FPS);
		if (*completed)
			game->crowbar.equiped = 1;
	}
	else if (game->crowbar.state == ATTACK)
		*completed = handle_animation_state(game, &game->crowbar.attack, FPS);
	else if (game->crowbar.state == ATTACK_HIT)
		*completed = handle_animation_state(game, &game->crowbar.attack_hit,
				FPS);
	else if (game->crowbar.state == HOLSTER)
	{
		*completed = handle_animation_state(game, &game->crowbar.holster, FPS);
		if (*completed)
			game->crowbar.equiped = 0;
	}
	if (*completed)
		handle_crowbar_completed(game);
}
