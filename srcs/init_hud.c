/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:58 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 09:16:18 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_color_shading(t_data *game, t_image *img)
{
	int				i;
	int				j;
	unsigned int	t;
	t_color			color;
	t_color			new;

	i = 0;
	while (i < img->w)
	{
		j = 0;
		while (j < img->h)
		{
			t = get_image_color(img, j, i);
			if (t != TRANSPARENT_COLOR)
			{
				color = int_to_rgb(game->hud_color);
				shade_color(&color, t & 0xFF);
				set_rgb(color.r / 255, color.g / 255, color.b / 255, &new);
				set_image_color(img, j, i, rgb_to_int(new));
			}
			j++;
		}
		i++;
	}
}

void	init_hud(t_data *game)
{
	char			path[270];
	t_hud			*elem;
	DIR				*hud_dir;
	struct dirent	*dp;

	hud_dir = opendir("resources/hud");
	if (!hud_dir)
		exit(gc_free(game->gc, "Error\n Cannot open resources/hud", 2));
	dp = readdir(hud_dir);
	while (dp)
	{
		if (ft_strcmp(dp->d_name, ".") && ft_strcmp(dp->d_name, ".."))
		{
			elem = gc_malloc(sizeof(t_hud), &game->gc);
			elem->img = gc_malloc(sizeof(t_image), &game->gc);
			snprintf(elem->name, sizeof(elem->name), "%s", dp->d_name);
			snprintf(path, sizeof(path), "resources/hud/%s", elem->name);
			check_file(game, path, ".xpm");
			elem->img->w = 0;
			elem->img->h = 0;
			elem->img->ptr = NULL;
			elem->img->addr = NULL;
			elem->img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &elem->img->w, &elem->img->h);
			elem->img->addr = mlx_get_data_addr(elem->img->ptr, &elem->img->bpp, &elem->img->line_len, &elem->img->endian);
			apply_color_shading(game, elem->img);
			ft_lstadd_back(&game->hud_elem, ft_lstnew_gc(elem, &game->gc));
		}
		dp = readdir(hud_dir);
	}
	closedir(hud_dir);
}
