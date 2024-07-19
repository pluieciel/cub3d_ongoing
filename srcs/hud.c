/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:05:43 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/19 19:06:09 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_handgun_category(t_data *game)
{
	int	x;
	
	if (game->key.two)
	{
		x = 15;
    	x = render_hud_image(game, "hud_bucket1.xpm", x, 35) + 5;
    	x = render_hud_image(game, "hud_bucket2.xpm", x, 35) + 178;
    	x = render_hud_image(game, "hud_bucket3.xpm", x, 35) + 5;
    	x = render_hud_image(game, "hud_bucket4.xpm", x, 35) + 5;
    	x = render_hud_image(game, "hud_bucket5.xpm", x, 35) + 5;
		x = 15;
		x = render_hud_image(game, "hud_bucket0.xpm", x, 59) + 5;
		render_hud_image(game, "hud_handgun.xpm", x, 87);
		x = render_hud_image(game, "hud_selection.xpm", x, 87);
	}
}

static void draw_crowbar_category(t_data *game)
{
	int	x;
	
	if (game->key.one)
	{
		x = 15;
    	x = render_hud_image(game, "hud_bucket1.xpm", x, 35) + 178;
    	x = render_hud_image(game, "hud_bucket2.xpm", x, 35) + 5;
    	x = render_hud_image(game, "hud_bucket3.xpm", x, 35) + 5;
    	x = render_hud_image(game, "hud_bucket4.xpm", x, 35) + 5;
    	x = render_hud_image(game, "hud_bucket5.xpm", x, 35) + 5;
		x = 15;
		render_hud_image(game, "hud_crowbar.xpm", x, 87);
		x = render_hud_image(game, "hud_selection.xpm", x, 87) + 6;
		x = render_hud_image(game, "hud_bucket0.xpm", x, 59);
	}
}

void	draw_hud(t_data *game)
{
	int	x;

    x = 20;
    x = render_hud_image(game, "hud_cross.xpm", x, WIN_H - 20) + 10;
    x = render_hud_image(game, "hud_number_1.xpm", x, WIN_H - 20) + 10;
    x = render_hud_image(game, "hud_number_0.xpm", x, WIN_H - 20) + 7;
    x = render_hud_image(game, "hud_number_0.xpm", x, WIN_H - 20) + 20;
    x = render_hud_image(game, "hud_divider.xpm", x, WIN_H - 20) + 20;
    x = render_hud_image(game, "hud_suit_full.xpm", x, WIN_H - 15) + 10;
    x = render_hud_image(game, "hud_number_1.xpm", x, WIN_H - 20) + 10;
    x = render_hud_image(game, "hud_number_0.xpm", x, WIN_H - 20) + 7;
    x = render_hud_image(game, "hud_number_0.xpm", x, WIN_H - 20);
	draw_handgun_category(game);
	draw_crowbar_category(game);
    draw_minimap(game);
}