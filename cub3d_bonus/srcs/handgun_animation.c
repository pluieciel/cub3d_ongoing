/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handgun_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:22 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 17:22:28 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_handgun_idle_state(t_data *game)
{
	if (game->handgun.equiped)
	{
		render_image(game, (t_image *)game->handgun.shoot.head->content, 0, 0);
		check_collision(game, game->player.dir_x, game->player.dir_y, COLL_DIS);
		if (game->left_click)
			game->handgun.state = SHOOT;
		else if (game->key.one || game->key.three)
			game->handgun.state = HOLSTER;
	}
	else if (game->key.two)
		game->handgun.state = DRAW;
}

static void	handle_handgun_completed(t_data *game)
{
	if (game->key.one)
	{
		game->handgun.state = NONE;
		game->crowbar.state = DRAW;
	}
	else if (game->key.three)
	{
		game->handgun.state = NONE;
		game->shotgun.state = DRAW;
	}
	if (game->handgun.state != NONE)
	{
		game->handgun.state = IDLE;
		game->key.one = 0;
		game->key.two = 0;
		game->key.three = 0;
	}
}

void	update_handgun_state(t_data *game)
{
	bool	*completed;

	completed = &game->handgun.completed;
	*completed = 0;
	if (game->handgun.state == IDLE)
		handle_handgun_idle_state(game);
	else if (game->handgun.state == DRAW)
	{
		*completed = handle_animation_state(game, &game->handgun.draw, FPS);
		if (*completed)
			game->handgun.equiped = 1;
	}
	else if (game->handgun.state == SHOOT)
		*completed = handle_animation_state(game, &game->handgun.shoot, FPS
				/ 2);
	else if (game->handgun.state == HOLSTER)
	{
		*completed = handle_animation_state(game, &game->handgun.holster, FPS);
		if (*completed)
			game->handgun.equiped = 0;
	}
	if (*completed)
		handle_handgun_completed(game);
}
