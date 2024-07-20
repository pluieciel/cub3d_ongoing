/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:18 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 11:34:01 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_door_h(t_raycast *ray, int col, int row)
{
	float			r;
	float			c;
	unsigned int	t;
	float			shadow;
	float			offset;

	if (ray->doors_h[ray->num_doors_h].dis < ray->nearest_wall_dis)
	{
		shadow = 1.0 - (fmin(ray->doors_h[ray->num_doors_h].dis, 8 * B_SIZE) / (8
					* B_SIZE));
		if (ray->doors_h[ray->num_doors_h].dir == 1)
			c = round(fmod(ray->doors_h[ray->num_doors_h].x, B_SIZE) / B_SIZE
					* ray->g->img_door.w);
		else
			c = round((1 - fmod(ray->doors_h[ray->num_doors_h].x, B_SIZE)
						/ B_SIZE) * ray->g->img_door.w);
		r = round((1 - fmod(ray->doors_h[ray->num_doors_h].z + 32
						+ ray->g->player.z, B_SIZE) / B_SIZE)
				* ray->g->img_door.h);
		offset = (ray->g->map[(int)ray->doors_h[ray->num_doors_h].map_y][(int)ray->doors_h[ray->num_doors_h].map_x]
				- 2) * ray->g->img_door.w;
		if ((int)c < ray->g->img_door.w / 2 && (int)c
			+ (int)offset < ray->g->img_door.w / 2)
		{
			t = ((unsigned int *)ray->g->img_door.addr)[(int)r
				* ray->g->img_door.w + (int)c + (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->g->img.addr)[row * WIN_W
					+ col] = (((int)round(((t >> 16) & 0xff)
								* shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t)&0xff) * shadow) & 0xff);
		}
		else if ((int)c > ray->g->img_door.w / 2 && (int)c
			- (int)offset > ray->g->img_door.w / 2)
		{
			t = ((unsigned int *)ray->g->img_door.addr)[(int)r
				* ray->g->img_door.w + (int)c - (int)offset];
			if (t != TRANSPARENT_COLOR)
				((unsigned int *)ray->g->img.addr)[row * WIN_W
					+ col] = (((int)round(((t >> 16) & 0xff)
								* shadow) & 0xff) << 16)
					+ (((int)round(((t >> 8) & 0xff) * shadow) & 0xff) << 8)
					+ ((int)round(((t)&0xff) * shadow) & 0xff);
		}
	}
	ray->num_doors_h--;
}

void	draw_door_v(t_raycast *ray, int col, int row)
{
	float			r;
	float			c;
	unsigned int	t;
	float			shadow;
	float			offset;
	t_color			color;

	if (ray->doors_v[ray->num_doors_v].dis < ray->nearest_wall_dis)
	{
		shadow = 1.0 - (fmin(ray->doors_v[ray->num_doors_v].dis, 8 * B_SIZE) / (8
					* B_SIZE));
		if (ray->doors_v[ray->num_doors_v].dir == 1)
			c = round(fmod(ray->doors_v[ray->num_doors_v].y, B_SIZE) / B_SIZE
					* ray->g->img_door.w);
		else
			c = round((1 - fmod(ray->doors_v[ray->num_doors_v].y, B_SIZE)
						/ B_SIZE) * ray->g->img_door.w);
		r = round((1 - fmod(ray->doors_v[ray->num_doors_v].z + 32
						+ ray->g->player.z, B_SIZE) / B_SIZE)
				* ray->g->img_door.h);
		offset = (ray->g->map[(int)ray->doors_v[ray->num_doors_v].map_y][(int)ray->doors_v[ray->num_doors_v].map_x]
				- 2) * ray->g->img_door.w;
		if ((int)c < ray->g->img_door.w / 2 && (int)c
			+ (int)offset < ray->g->img_door.w / 2)
		{
			t = get_image_color(&ray->g->img_door, r, c + offset);
			if (t != TRANSPARENT_COLOR)
			{
				color = int_to_rgb(t);
				shade_color(&color, shadow);
				set_image_color(&ray->g->img, row, col, rgb_to_int(color));
			}
		}
		else if ((int)c > ray->g->img_door.w / 2 && (int)c
			- (int)offset > ray->g->img_door.w / 2)
		{
			t = get_image_color(&ray->g->img_door, r, c - offset);
			if (t != TRANSPARENT_COLOR)
			{
				color = int_to_rgb(t);
				shade_color(&color, shadow);
				set_image_color(&ray->g->img, row, col, rgb_to_int(color));
			}
		}
	}
	ray->num_doors_v--;
}

void	draw_textures(t_data *g)
{
	t_raycast	ray[NUM_THREADS];
	int			i;

	i = -1;
	while (++i < NUM_THREADS)
	{
		ray[i].g = g;
		ray[i].v_down = &g->player.v_down;
		ray[i].v_right = &g->player.v_right;
		ray[i].col_start = i * (WIN_W / NUM_THREADS);
		ray[i].col_end = (i + 1) * (WIN_W / NUM_THREADS);
		ray[i].p.x = g->player.dir3d.x * g->dis_p_s - g->player.v_down.x
			* WIN_H / 2 - g->player.v_right.x * WIN_W / 2 + g->player.v_right.x
			* ray[i].col_start;
		ray[i].p.y = g->player.dir3d.y * g->dis_p_s - g->player.v_down.y
			* WIN_H / 2 - g->player.v_right.y * WIN_W / 2 + g->player.v_right.y
			* ray[i].col_start;
		ray[i].p.z = g->player.dir3d.z * g->dis_p_s - g->player.v_down.z
			* WIN_H / 2 - g->player.v_right.z * WIN_W / 2 + g->player.v_right.z
			* ray[i].col_start;
		pthread_create(&ray[i].thread, NULL, render_section, &ray[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(ray[i].thread, NULL);
}
