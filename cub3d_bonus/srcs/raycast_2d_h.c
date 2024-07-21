/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2d_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:45 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 17:07:59 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	cast_ray(t_data *g, float x, float y, bool type)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE && g->rc_h.x / B_SIZE > 0
		&& g->rc_h.x / B_SIZE < g->map_w)
	{
		g->rc_h.map_y = (int)g->rc_h.y / B_SIZE - (y < 0);
		g->rc_h.map_x = (int)g->rc_h.x / B_SIZE;
		if (y != 0 && g->rc_h.map_y >= 0 && g->rc_h.map_y < g->map_h
			&& is_collider(g, g->rc_h.map_x, g->rc_h.map_y, type))
			return (distance(g->rc_h.x, g->rc_h.y, g->player.x, g->player.y));
		range++;
		g->rc_h.x += x / fabs(y) * B_SIZE;
		g->rc_h.y += ((y > 0) * 2 - 1) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_2d_h(t_data *g, float x, float y, bool type)
{
	if (y < 0)
	{
		g->rc_h.y = g->player.y - g->player.y % B_SIZE;
		g->rc_h.x = g->player.x - (g->player.y % B_SIZE) * x / y;
		g->rc_h.dir = -1;
	}
	else if (y > 0)
	{
		g->rc_h.y = g->player.y + B_SIZE - g->player.y % B_SIZE;
		g->rc_h.x = g->player.x
			+ (B_SIZE - g->player.y % B_SIZE) * x / y;
		g->rc_h.dir = 1;
	}
	else
	{
		g->rc_h.x = g->player.x;
		g->rc_h.y = g->player.y;
		g->rc_h.dir = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (cast_ray(g, x, y, type));
}
