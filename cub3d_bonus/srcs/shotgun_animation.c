/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shotgun_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:22 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/19 23:12:17 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_shotgun_idle_state(t_data *game)
{
	if (game->shotgun.equiped)
	{
		render_image(game, (t_image *)game->shotgun.shoot.head->content, 0, 0);
		check_collision(game, game->player.dir_x, game->player.dir_y, COLL_DIS);
		if (game->left_click)
			game->shotgun.state = SHOOT;
		else if (game->key.one || game->key.two)
			game->shotgun.state = HOLSTER;
	}
	else if (game->key.three)
		game->shotgun.state = DRAW;
}

static void	handle_shotgun_completed(t_data *game)
{
	if (game->key.one)
	{
		game->shotgun.state = NONE;
		game->crowbar.state = DRAW;
	}
	else if (game->key.two)
	{
		game->shotgun.state = NONE;
		game->handgun.state = DRAW;
	}
	if (game->shotgun.state != NONE)
	{
		game->shotgun.state = IDLE;
		game->key.one = 0;
		game->key.two = 0;
		game->key.three = 0;
	}
}

void	update_shotgun_state(t_data *game)
{
	bool	*completed;

	completed = &game->shotgun.completed;
	*completed = 0;
	if (game->shotgun.state == IDLE)
		handle_shotgun_idle_state(game);
	else if (game->shotgun.state == DRAW)
	{
		*completed = handle_animation_state(game, &game->shotgun.draw, FPS);
		if (*completed)
			game->shotgun.equiped = 1;
	}
	else if (game->shotgun.state == SHOOT)
		*completed = handle_animation_state(game, &game->shotgun.shoot, FPS
				/ 2);
	else if (game->shotgun.state == HOLSTER)
	{
		*completed = handle_animation_state(game, &game->shotgun.holster, FPS);
		if (*completed)
			game->shotgun.equiped = 0;
	}
	if (*completed)
		handle_shotgun_completed(game);
}
