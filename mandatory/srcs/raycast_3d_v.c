/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d_v.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:52 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 00:00:59 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static float	cast_ray(t_raycast *r)
{
	int	range;

	range = 0;
	while (range < RAYCAST_RANGE && r->rc_v.y / B_SIZE > 0 && r->rc_v.y / B_SIZE < r->g->map_h && r->rc_v.z + r->g->player.z <= B_SIZE / 2 && r->rc_v.z + r->g->player.z >= -B_SIZE / 2)
	{
		r->rc_v.map_x = (int)r->rc_v.x / B_SIZE - (r->p.x < 0);
		r->rc_v.map_y = (int)r->rc_v.y / B_SIZE;
		if (r->p.x != 0 && r->rc_v.map_x >= 0 && r->rc_v.map_x < r->g->map_w)
		{
			if (r->g->map[(int)r->rc_v.map_y][(int)r->rc_v.map_x] == 1)
				return (distance(r->rc_v.x, r->rc_v.y, r->g->player.x, r->g->player.y));
		}
		range++;
		r->rc_v.y += r->p.y / fabs(r->p.x) * B_SIZE;
		r->rc_v.x += ((r->p.x > 0) * 2 - 1) * B_SIZE;
		r->rc_v.z += r->p.z / fabs(r->p.x) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_3d_v(t_raycast *r)
{
	if (r->p.x < 0)
	{
		r->rc_v.x = r->g->player.x - r->g->player.x % B_SIZE;
		r->rc_v.y = r->g->player.y - (r->g->player.x % B_SIZE) * r->p.y / r->p.x;
		r->rc_v.z = (r->g->player.x % B_SIZE) * r->p.z / -r->p.x;
		r->rc_v.dir = -1;
	}
	else if (r->p.x > 0)
	{
		r->rc_v.x = r->g->player.x + B_SIZE - r->g->player.x % B_SIZE;
		r->rc_v.y = r->g->player.y + (B_SIZE - r->g->player.x % B_SIZE) * r->p.y / r->p.x;
		r->rc_v.z = (B_SIZE - r->g->player.x % B_SIZE) * r->p.z / r->p.x;
		r->rc_v.dir = 1;
	}
	else
	{
		reset_ray(r, &r->rc_v);
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (cast_ray(r));
}
