/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:02:56 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 00:43:27 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	reset_ray(t_raycast *ray, t_res_rc *rc)
{
	rc->x = ray->g->player.x;
	rc->y = ray->g->player.y;
	rc->z = ray->g->player.z;
	rc->dir = 0;
}

void	raycast_3d(t_raycast *ray)
{
	ray->rc_h.dis = raycast_3d_h(ray);
	ray->rc_v.dis = raycast_3d_v(ray);
	if (ray->rc_h.dis < ray->rc_v.dis)
		ray->rc = &ray->rc_h;
	else
		ray->rc = &ray->rc_v;
}
