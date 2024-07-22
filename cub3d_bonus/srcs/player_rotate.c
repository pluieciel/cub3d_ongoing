/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <jlefonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:32 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/22 09:20:01 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rotate_vertical_view(t_data *game)
{
	if (game->key.up && game->player.dir3d.z < 0.95)
	{
		rotate_u(&game->player.dir3d, game->player.dir3d, game->player.v_down,
			-ROT_SPEED);
		get_vector_down(game, &game->player.v_right, &game->player.v_down);
	}
	else if (game->key.down && game->player.dir3d.z > -0.95)
	{
		rotate_u(&game->player.dir3d, game->player.dir3d, game->player.v_down,
			ROT_SPEED);
		get_vector_down(game, &game->player.v_right, &game->player.v_down);
	}
}

void	rotate_player(t_data *game, float dir_x, float dir_y, t_point3d *dir3d)
{
	if (game->key.left)
	{
		game->player.dir_x = dir_x * cos(-ROT_SPEED) - dir_y * sin(-ROT_SPEED);
		game->player.dir_y = dir_x * sin(-ROT_SPEED) + dir_y * cos(-ROT_SPEED);
		game->player.dir3d.x = dir3d->x * cos(-ROT_SPEED) - dir3d->y
			* sin(-ROT_SPEED);
		game->player.dir3d.y = dir3d->x * sin(-ROT_SPEED) + dir3d->y
			* cos(-ROT_SPEED);
	}
	else if (game->key.right)
	{
		game->player.dir_x = dir_x * cos(ROT_SPEED) - dir_y * sin(ROT_SPEED);
		game->player.dir_y = dir_x * sin(ROT_SPEED) + dir_y * cos(ROT_SPEED);
		game->player.dir3d.x = dir3d->x * cos(ROT_SPEED) - dir3d->y
			* sin(ROT_SPEED);
		game->player.dir3d.y = dir3d->x * sin(ROT_SPEED) + dir3d->y
			* cos(ROT_SPEED);
	}
	get_vector_right(game, &game->player.v_right);
	get_vector_down(game, &game->player.v_right, &game->player.v_down);
	rotate_vertical_view(game);
}
