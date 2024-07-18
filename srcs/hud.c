/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:44 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/18 15:08:44 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_image	*get_hud_image(t_data *game, char *name)
{
	t_list	*hud_elem;
	t_hud	*hud;

	hud_elem = game->hud_elem;
	while (hud_elem)
	{
		hud = (t_hud *)hud_elem->content;
		if (!ft_strcmp(hud->name, name))
			return (hud->img);
		hud_elem = hud_elem->next;
	}
	return (NULL);
}

static void	render_hud_image(t_data *game, char *name, int *x, int y)
{
	t_image	*img;

	img = get_hud_image(game, name);
	if (img)
	{
		render_image(game, img, WIN_W - img->w - *x, WIN_H - img->h - y);
		*x += img->w;
	}
}

void	draw_hud(t_data *game)
{
	int	x;

	x = WIN_W - 40;
	render_hud_image(game, "hud_cross.xpm", &x, 20);
	x -= 45;
	render_hud_image(game, "hud_number_1.xpm", &x, 20);
	x -= 30;
	render_hud_image(game, "hud_number_0.xpm", &x, 20);
	x -= 35;
	render_hud_image(game, "hud_number_0.xpm", &x, 20);
	x -= 35;
	render_hud_image(game, "hud_divider.xpm", &x, 20);
	x -= 50;
	render_hud_image(game, "hud_suit_full.xpm", &x, 15);
	x -= 50;
	render_hud_image(game, "hud_number_1.xpm", &x, 20);
	x -= 30;
	render_hud_image(game, "hud_number_0.xpm", &x, 20);
	x -= 35;
	render_hud_image(game, "hud_number_0.xpm", &x, 20);
	draw_minimap(game);
}
