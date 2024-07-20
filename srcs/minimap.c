/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:14 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/18 16:27:17 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_block(t_data *game, t_point *p1, t_point *p2, t_color hud_c)
{
	t_color	c;
	t_color	c2;

	c = int_to_rgb(get_image_color(&game->img, p1->x, p1->y));
	if (game->map[p2->y][p2->x] == 1)
	{
		mix_color(&c, hud_c, 2, 1);
		shade_color(&c, 0.6);
		set_image_color(&game->img, p1->x, p1->y, rgb_to_int(c));
	}
	else if (game->map[p2->y][p2->x] == 3)
	{
		set_rgb(0, 0x80, 0, &c2);
		set_image_color(&game->img, p1->x, p1->y, rgb_to_int(*(mix_color(&c, c2, 1, 1))));
	}
	else if (game->map[p2->y][p2->x] >= 2)
	{
		set_rgb(0x80, 0, 0, &c2);
		set_image_color(&game->img, p1->x, p1->y, rgb_to_int(*(mix_color(&c, c2, 1, 1))));
	}
}

static void	draw_block(t_data *game, int i, int j, t_color hud_c)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	x = ((j - MM_POS_X) * B_SIZE / MM_FACTOR + game->player.x) / B_SIZE;
	y = ((i - MM_POS_Y) * B_SIZE / MM_FACTOR + game->player.y) / B_SIZE;
	if (x >= 0 && y >= 0 && x < game->map_w && y < game->map_h && game->map[y][x] >= 1 && distance(i, j, MM_POS_Y, MM_POS_X) < MM_RADIUS)
	{
		p1.y = round(-(j - MM_POS_X) * game->player.dir_y + (i - MM_POS_Y) * game->player.dir_x) + MM_POS_X;
		p1.x = round((j - MM_POS_X) * -game->player.dir_x - (i - MM_POS_Y) * game->player.dir_y) + MM_POS_Y;
		p2.x = x;
		p2.y = y;
		fill_block(game, &p1, &p2, hud_c);
	}
}

static void	draw_background(t_data *game, int i, int j, float angle)
{
	t_color	c;
	t_color	hud_c;

	hud_c = int_to_rgb(game->hud_color);
	if (distance(i, j, MM_POS_X, MM_POS_Y) < MM_RADIUS)
	{
		c = int_to_rgb(get_image_color(&game->img, j, i));
		if (MM_POS_Y > j && atan(1.0 * abs(i - MM_POS_X) / (MM_POS_Y - j)) < angle)
			set_image_color(&game->img, j, i, rgb_to_int(*mix_color(&c, hud_c, 1, 1)));
		else
			set_image_color(&game->img, j, i, rgb_to_int(*mix_color(&c, hud_c, 2, 1)));
	}
}

void	draw_minimap(t_data *game)
{
	int		i;
	int		j;
	float	angle;

	angle = atan(1.0 * (WIN_W / 2) / game->dis_p_s);
	i = MM_POS_X - MM_RADIUS - 1;
	while (++i <= MM_POS_X + MM_RADIUS)
	{
		j = MM_POS_Y - MM_RADIUS - 1;
		while (++j <= MM_POS_Y + MM_RADIUS)
			draw_background(game, i, j, angle);
	}
	i = MM_POS_Y - MM_RADIUS - 1;
	while (++i <= MM_POS_Y + MM_RADIUS)
	{
		j = MM_POS_X - MM_RADIUS - 1;
		while (++j <= MM_POS_X + MM_RADIUS)
			draw_block(game, i, j, int_to_rgb(game->hud_color));
	}
}
