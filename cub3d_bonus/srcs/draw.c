/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <jlefonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:11 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/22 09:40:04 by jlefonde         ###   ########.fr       */
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

static void	draw_floor(t_raycast *ray, int row, int col)
{
	float	r;
	float	c;
	float	shadow;
	t_color	color;

	ray->rc->x = (ray->rc->x - ray->g->player.x) * (-32 - ray->g->player.z)
		/ ray->rc->z + ray->g->player.x;
	ray->rc->y = (ray->rc->y - ray->g->player.y) * (-32 - ray->g->player.z)
		/ ray->rc->z + ray->g->player.y;
	c = fmod(ray->rc->x, B_SIZE) / B_SIZE;
	c += (c < 0);
	c = round((1 - c) * (ray->g->img_floor.w - 1));
	r = fmod(ray->rc->y, B_SIZE) / B_SIZE;
	r += (r < 0);
	r = round((1 - r) * (ray->g->img_floor.h - 1));
	ray->rc->dis = distance(ray->rc->x, ray->rc->y, ray->g->player.x,
			ray->g->player.y);
	shadow = 1.0 - (fmin(ray->rc->dis, 8 * B_SIZE) / (8 * B_SIZE));
	color = int_to_rgb(get_image_color(&ray->g->img_floor, r, c));
	shade_color(&color, shadow);
	set_image_color(&ray->g->img, row, col, rgb_to_int(color));
}

static void	draw_sky(t_raycast *ray, int row, int col)
{
	float			temp_x;
	float			temp_y;
	float			r;
	float			c;
	unsigned int	color;

	temp_x = ray->rc->x - ray->g->player.x;
	temp_y = ray->rc->y - ray->g->player.y;
	r = ray->rc->z / sqrt(temp_x * temp_x + temp_y * temp_y + ray->rc->z
			* ray->rc->z);
	r = fmin(1.0, r);
	r = 1.0 - asin(r) / (M_PI / 2);
	if (temp_x != 0)
		c = (atan(temp_y / temp_x) + M_PI * (temp_x < 0) + (M_PI / 2)) / (M_PI
				* 2);
	else
		c = 1.0 / 4 + 1.0 / 2 * (temp_y < 0);
	r *= ray->g->img_sky.h;
	c *= ray->g->img_sky.w;
	color = get_image_color(&ray->g->img_sky, r, c);
	set_image_color(&ray->g->img, row, col, color);
}

static void	draw_door(t_raycast *ray, int row, int col)
{
	float	door_h_dis;
	float	door_v_dis;

	while (ray->num_doors_h >= 0 || ray->num_doors_v >= 0)
	{
		door_h_dis = ray->doors_h[ray->num_doors_h].dis;
		door_v_dis = ray->doors_v[ray->num_doors_v].dis;
		if (ray->num_doors_h < 0)
			draw_door_v(ray, col, row);
		else if (ray->num_doors_v < 0)
			draw_door_h(ray, col, row);
		else if (door_h_dis < door_v_dis)
			draw_door_v(ray, col, row);
		else
			draw_door_h(ray, col, row);
	}
}

void	draw_pixel(t_raycast *ray, int col, int row)
{
	ray->nearest_wall_dis = RAYCAST_RANGE * B_SIZE;
	if (ray->rc->dir != 0 && ray->rc->z + ray->g->player.z >= -32 && ray->rc->z
		+ ray->g->player.z <= 32)
		draw_wall(ray, row, col);
	else if (ray->rc->z + ray->g->player.z < -32)
		draw_floor(ray, row, col);
	else if (ray->rc->z >= 0)
		draw_sky(ray, row, col);
	draw_door(ray, row, col);
}
