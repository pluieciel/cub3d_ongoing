/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2d_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:45 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 17:07:38 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	cast_ray(t_data *g, float x, float y, bool type)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE && g->rc_v.y / B_SIZE > 0
		&& g->rc_v.y / B_SIZE < g->map_h)
	{
		g->rc_v.map_y = (int)g->rc_v.y / B_SIZE;
		g->rc_v.map_x = (int)g->rc_v.x / B_SIZE - (x < 0);
		if (x != 0 && g->rc_v.map_x >= 0 && g->rc_v.map_x < g->map_w
			&& is_collider(g, g->rc_v.map_x, g->rc_v.map_y, type))
			return (distance(g->rc_v.x, g->rc_v.y, g->player.x, g->player.y));
		range++;
		g->rc_v.y += y / fabs(x) * B_SIZE;
		g->rc_v.x += ((x > 0) * 2 - 1) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_2d_v(t_data *g, float x, float y, bool type)
{
	if (x < 0)
	{
		g->rc_v.x = g->player.x - g->player.x % B_SIZE;
		g->rc_v.y = g->player.y - (g->player.x % B_SIZE) * y / x;
		g->rc_v.dir = -1;
	}
	else if (x > 0)
	{
		g->rc_v.x = g->player.x + B_SIZE - g->player.x % B_SIZE;
		g->rc_v.y = g->player.y + (B_SIZE - g->player.x % B_SIZE) * y / x;
		g->rc_v.dir = 1;
	}
	else
	{
		g->rc_v.x = g->player.x;
		g->rc_v.y = g->player.y;
		g->rc_v.dir = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (cast_ray(g, x, y, type));
}
