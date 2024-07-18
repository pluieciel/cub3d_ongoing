/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:55 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/18 15:14:07 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_hud_image(t_data *game, char *name, int *x, int y)
{
	t_image	*img;

	img = get_hud_image(game, name);
	if (img)
	{
		render_image(game, img, WIN_W - img->w - *x, WIN_H - img->h - y);
		*x += img->w;
	}
}

void	render_image(t_data *game, t_image *img, int x, int y)
{
	int				i;
	int				j;
	int				dest_x;
	int				dest_y;
	unsigned int	color;

	if (!img)
		return ;
	i = 0;
	while (i < WIN_W && i < img->w)
	{
		j = 0;
		while (j < WIN_H && j < img->h)
		{
			color = get_image_color(img, j, i);
			dest_x = i + x;
			dest_y = j + y;
			if (dest_x >= 0 && dest_x < WIN_W && dest_y >= 0 && dest_y < WIN_H
				&& color != TRANSPARENT_COLOR)
				((unsigned int *)game->img.addr)[dest_y * WIN_W + dest_x] = color;
			j++;
		}
		i++;
	}
}

void	*render_section(void *arg)
{
	t_raycast	*ray;
	int			col;
	int			row;

	ray = (t_raycast *)arg;
	col = ray->col_start - 1;
	while (++col < ray->col_end)
	{
		row = -1;
		while (++row < WIN_H)
		{
			raycast_3d(ray);
			draw_pixel(ray, col, row);
			ray->p.x += ray->v_down->x;
			ray->p.y += ray->v_down->y;
			ray->p.z += ray->v_down->z;
		}
		ray->p.x -= ray->v_down->x * WIN_H;
		ray->p.y -= ray->v_down->y * WIN_H;
		ray->p.z -= ray->v_down->z * WIN_H;
		ray->p.x += ray->v_right->x;
		ray->p.y += ray->v_right->y;
		ray->p.z += ray->v_right->z;
	}
	return (NULL);
}

int	render(t_data *game)
{
	__uint64_t	current_time;

	current_time = get_timestamp_ms();
	if (game->win_ptr != NULL && (current_time - game->time) > 1000 / FPS)
	{
		game->time = current_time;
		ft_bzero(game->img.addr, game->img.w * game->img.h * (game->img.bpp / 8));
		update_doors(game);
		update_player(game);
		draw_textures(game);
		draw_hud(game);
		update_animation(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.ptr, 0, 0);
	}
	return (0);
}
