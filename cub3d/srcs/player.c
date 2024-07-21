/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:42 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 00:00:37 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
}
