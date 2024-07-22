/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <jlefonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:02:56 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/22 09:20:24 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_collider(t_data *game, int x, int y, bool type)
{
	return (game->map[y][x] == 1 || game->map[y][x] == 2 || (type
			&& game->map[y][x] == 3));
}

void	reset_ray(t_raycast *ray, t_res_rc *rc)
{
	rc->x = ray->g->player.x;
	rc->y = ray->g->player.y;
	rc->z = ray->g->player.z;
	rc->dir = 0;
}

void	add_door(t_raycast *ray, t_res_rc *rc, t_res_rc *doors, int *num_doors)
{
	(*num_doors)++;
	doors[*num_doors].x = rc->x;
	doors[*num_doors].y = rc->y;
	doors[*num_doors].z = rc->z;
	doors[*num_doors].dis = distance(rc->x, rc->y, ray->g->player.x,
			ray->g->player.y);
	doors[*num_doors].dir = rc->dir;
	doors[*num_doors].map_x = rc->map_x;
	doors[*num_doors].map_y = rc->map_y;
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

void	raycast_3d(t_raycast *ray)
{
	ray->num_doors_h = -1;
	ray->num_doors_v = -1;
	ray->rc_h.dis = raycast_3d_h(ray);
	ray->rc_v.dis = raycast_3d_v(ray);
	if (ray->rc_h.dis < ray->rc_v.dis)
		ray->rc = &ray->rc_h;
	else
		ray->rc = &ray->rc_v;
}
