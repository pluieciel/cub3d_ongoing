/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:18 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 12:46:49 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_door_shading(t_raycast *ray, t_point *p1, t_point *p2, t_res_rc *door)
{
	float			shadow;
	unsigned int	t;
	t_color			color;

	shadow = 1.0 - (fmin(door->dis, 8 * B_SIZE) / (8 * B_SIZE));
	t = get_image_color(&ray->g->img_door, p2->y, p2->x);
	if (t != TRANSPARENT_COLOR)
	{
		color = int_to_rgb(t);
		shade_color(&color, shadow);
		set_image_color(&ray->g->img, p1->y, p1->x, rgb_to_int(color));
	}
}

static void	update_door_texture_pos(t_raycast *ray, t_point *p1, t_point *p2, t_res_rc *door)
{
	float	offset;

	offset = (ray->g->map[(int)door->map_y][(int)door->map_x] - 2) * ray->g->img_door.w;
	if (p2->x < ray->g->img_door.w / 2 && p2->x + offset < ray->g->img_door.w / 2)
	{
		p2->x += offset;
		apply_door_shading(ray, p1, p2, door);
	}
	else if (p2->x > ray->g->img_door.w / 2 && p2->x - offset > ray->g->img_door.w / 2)
	{
		p2->x -= offset;
		apply_door_shading(ray, p1, p2, door);
	}
}

void	draw_door_h(t_raycast *ray, int col, int row)
{
	t_point	p1;
	t_point	p2;

	if (ray->doors_h[ray->num_doors_h].dis < ray->nearest_wall_dis)
	{
		if (ray->doors_h[ray->num_doors_h].dir == 1)
			p2.x = round(fmod(ray->doors_h[ray->num_doors_h].x, B_SIZE) / B_SIZE * ray->g->img_door.w);
		else
			p2.x = round((1 - fmod(ray->doors_h[ray->num_doors_h].x, B_SIZE) / B_SIZE) * ray->g->img_door.w);
		p2.y = round((1 - fmod(ray->doors_h[ray->num_doors_h].z + 32 + ray->g->player.z, B_SIZE) / B_SIZE) * ray->g->img_door.h);
		p1.x = col;
		p1.y = row;
		update_door_texture_pos(ray, &p1, &p2, &ray->doors_h[ray->num_doors_h]);
	}
	ray->num_doors_h--;
}

void	draw_door_v(t_raycast *ray, int col, int row)
{
	t_point	p1;
	t_point	p2;

	if (ray->doors_v[ray->num_doors_v].dis < ray->nearest_wall_dis)
	{
		if (ray->doors_v[ray->num_doors_v].dir == 1)
			p2.x = round(fmod(ray->doors_v[ray->num_doors_v].y, B_SIZE) / B_SIZE * ray->g->img_door.w);
		else
			p2.x = round((1 - fmod(ray->doors_v[ray->num_doors_v].y, B_SIZE) / B_SIZE) * ray->g->img_door.w);
		p2.y = round((1 - fmod(ray->doors_v[ray->num_doors_v].z + 32 + ray->g->player.z, B_SIZE) / B_SIZE) * ray->g->img_door.h);
		p1.x = col;
		p1.y = row;
		update_door_texture_pos(ray, &p1, &p2, &ray->doors_v[ray->num_doors_v]);
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
