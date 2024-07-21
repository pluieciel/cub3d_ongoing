/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:07:45 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 17:22:28 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_collision(t_data *game, float dir_x, float dir_y, int coll_dis)
{
	raycast_2d(game, dir_x, dir_y, (coll_dis == OPEN_DIS));
	if (game->rc_h.dis < coll_dis && game->rc_h.dis < game->rc_v.dis)
	{
		game->coll_wall_h = 1;
		if (coll_dis == OPEN_DIS)
			game->coll_door_h = 1;
	}
	if (game->rc_v.dis < coll_dis && game->rc_v.dis < game->rc_h.dis)
	{
		game->coll_wall_v = 1;
		if (coll_dis == OPEN_DIS)
			game->coll_door_v = 1;
	}
}

void	check_collisions(t_data *game, float dir_x, float dir_y, float scale)
{
	check_collision(game, dir_x, dir_y, COLL_DIS);
	check_collision(game, dir_y, -dir_x, COLL_DIS);
	check_collision(game, -dir_y, dir_x, COLL_DIS);
	check_collision(game, scale * (dir_x - dir_y), scale * (dir_x + dir_y), COLL_DIS);
	check_collision(game, scale * (dir_x + dir_y), scale * (-dir_x + dir_y), COLL_DIS);
}
