/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:02:56 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 17:11:11 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_collider(t_data *g, int x, int y, bool type)
{
	return (g->map[y][x] == 1 || g->map[y][x] == 2 || (type && g->map[y][x] == 3));
}

void	raycast_2d(t_data *game, float x, float y, bool type)
{
	game->rc_h.dis = raycast_2d_h(game, x, y, type);
	game->rc_v.dis = raycast_2d_v(game, x, y, type);
	if (game->rc_h.dis < game->rc_v.dis)
		game->rc = &game->rc_h;
	else
		game->rc = &game->rc_v;
}
