/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:35 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 00:00:09 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_forward(t_data *game, float dir_x, float dir_y)
{
	game->player.x += round(dir_x * SPEED);
	game->player.y += round(dir_y * SPEED);
}

static void	move_backward(t_data *game, float dir_x, float dir_y)
{
	game->player.x -= round(dir_x * SPEED);
	game->player.y -= round(dir_y * SPEED);
}

static void	move_left(t_data *game, float dir_x, float dir_y)
{
	game->player.x += round(dir_y * SPEED);
	game->player.y -= round(dir_x * SPEED);
}

static void	move_right(t_data *game, float dir_x, float dir_y)
{
	game->player.x -= round(dir_y * SPEED);
	game->player.y += round(dir_x * SPEED);
}

void	move_player(t_data *game, float dir_x, float dir_y)
{
	if (game->key.w)
		move_forward(game, dir_x, dir_y);
	else if (game->key.s)
		move_backward(game, dir_x, dir_y);
	if (game->key.a)
		move_left(game, dir_x, dir_y);
	else if (game->key.d)
		move_right(game, dir_x, dir_y);
}
