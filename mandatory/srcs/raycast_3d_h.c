/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d_h.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:50 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 00:00:51 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	cast_ray(t_raycast *r)
{
	int	range;

	range = 0;
	while (range < RAYCAST_RANGE && r->rc_h.x / B_SIZE > 0 && r->rc_h.x / B_SIZE < r->g->map_w && r->rc_h.z + r->g->player.z <= B_SIZE / 2 && r->rc_h.z + r->g->player.z >= -B_SIZE / 2)
	{
		r->rc_h.map_x = (int)r->rc_h.x / B_SIZE;
		r->rc_h.map_y = (int)r->rc_h.y / B_SIZE - (r->p.y < 0);
		if (r->p.y != 0 && r->rc_h.map_y >= 0 && r->rc_h.map_y < r->g->map_h)
		{
			if (r->g->map[(int)r->rc_h.map_y][(int)r->rc_h.map_x] == 1)
				return (distance(r->rc_h.x, r->rc_h.y, r->g->player.x, r->g->player.y));
		}
		range++;
		r->rc_h.x += r->p.x / fabs(r->p.y) * B_SIZE;
		r->rc_h.y += ((r->p.y > 0) * 2 - 1) * B_SIZE;
		r->rc_h.z += r->p.z / fabs(r->p.y) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_3d_h(t_raycast *r)
{
	if (r->p.y < 0)
	{
		r->rc_h.y = r->g->player.y - r->g->player.y % B_SIZE;
		r->rc_h.x = r->g->player.x - (r->g->player.y % B_SIZE) * r->p.x / r->p.y;
		r->rc_h.z = (r->g->player.y % B_SIZE) * r->p.z / -r->p.y;
		r->rc_h.dir = 1;
	}
	else if (r->p.y > 0)
	{
		r->rc_h.y = r->g->player.y + B_SIZE - r->g->player.y % B_SIZE;
		r->rc_h.x = r->g->player.x + (B_SIZE - r->g->player.y % B_SIZE) * r->p.x / r->p.y;
		r->rc_h.z = (B_SIZE - r->g->player.y % B_SIZE) * r->p.z / r->p.y;
		r->rc_h.dir = -1;
	}
	else
	{
		reset_ray(r, &r->rc_h);
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (cast_ray(r));
}
