/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:11 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 00:47:26 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_wall(t_raycast *ray, int row, int col)
{
	float	shadow;
	t_color	color;

	shadow = 1.0 - (fmin(ray->rc->dis, 8 * B_SIZE) / (8 * B_SIZE));
	if (ray->rc == &ray->rc_h)
	{
		if (ray->rc->dir == 1)
			color = get_wall_color(ray, &ray->g->img_wall_no, ray->rc->x);
		else
			color = get_wall_color(ray, &ray->g->img_wall_so, ray->rc->x);
	}
	else
	{
		if (ray->rc->dir == 1)
			color = get_wall_color(ray, &ray->g->img_wall_ea, ray->rc->y);
		else
			color = get_wall_color(ray, &ray->g->img_wall_we, ray->rc->y);
	}
	shade_color(&color, shadow);
	set_image_color(&ray->g->img, row, col, rgb_to_int(color));
	ray->nearest_wall_dis = ray->rc->dis;
}

static void	init_ray(t_data *g, t_raycast *ray)
{
	ray->g = g;
	ray->v_down = &g->player.v_down;
	ray->v_right = &g->player.v_right;
	ray->p.x = g->player.dir3d.x * g->dis_p_s - g->player.v_down.x
		* WIN_H / 2 - g->player.v_right.x * WIN_W / 2;
	ray->p.y = g->player.dir3d.y * g->dis_p_s - g->player.v_down.y
		* WIN_H / 2 - g->player.v_right.y * WIN_W / 2;
	ray->p.z = g->player.dir3d.z * g->dis_p_s - g->player.v_down.z
		* WIN_H / 2 - g->player.v_right.z * WIN_W / 2;
}

void	draw_textures(t_data *g)
{
	int			col;
	int			row;
	t_raycast	ray;

	init_ray(g, &ray);
	col = -1;
	while (++col < WIN_W)
	{
		row = -1;
		while (++row < WIN_H)
		{
			raycast_3d(&ray);
			draw_pixel(&ray, col, row);
			ray.p.x += ray.v_down->x;
			ray.p.y += ray.v_down->y;
			ray.p.z += ray.v_down->z;
		}
		ray.p.x -= ray.v_down->x * WIN_H;
		ray.p.y -= ray.v_down->y * WIN_H;
		ray.p.z -= ray.v_down->z * WIN_H;
		ray.p.x += ray.v_right->x;
		ray.p.y += ray.v_right->y;
		ray.p.z += ray.v_right->z;
	}
}

void	draw_pixel(t_raycast *ray, int col, int row)
{
	t_color	color;
	float	shadow;

	ray->nearest_wall_dis = RAYCAST_RANGE * B_SIZE;
	if (ray->rc->dir != 0 && ray->rc->z + ray->g->player.z >= -32
		&& ray->rc->z + ray->g->player.z <= 32)
		draw_wall(ray, row, col);
	else if (ray->rc->z + ray->g->player.z < -32)
	{
		ray->rc->x = (ray->rc->x - ray->g->player.x) * (-32 - ray->g->player.z) / ray->rc->z + ray->g->player.x;
		ray->rc->y = (ray->rc->y - ray->g->player.y) * (-32 - ray->g->player.z) / ray->rc->z + ray->g->player.y;
		ray->rc->dis = distance(ray->rc->x, ray->rc->y, ray->g->player.x, ray->g->player.y);
		shadow = 1.0 - (fmin(ray->rc->dis, 8 * B_SIZE) / (8 * B_SIZE));
		color = int_to_rgb(ray->g->floor_color);
		shade_color(&color, shadow);
		set_image_color(&ray->g->img, row, col, rgb_to_int(color));
	}
	else if (ray->rc->z >= 0)
	{
		set_image_color(&ray->g->img, row, col, ray->g->ceiling_color);
	}
}
