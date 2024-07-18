/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:51 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/18 15:13:44 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_image(t_data *game, t_image **img, char *path)
{
	*img = gc_malloc(sizeof(t_image), &game->gc);
	(*img)->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &(*img)->w,
			&(*img)->h);
	(*img)->addr = mlx_get_data_addr((*img)->ptr, &(*img)->bpp,
			&(*img)->line_len, &(*img)->endian);
}

t_image	*get_hud_image(t_data *game, char *name)
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

unsigned int	get_image_color(t_image *img, int row, int col)
{
	return (((unsigned int *)img->addr)[row * img->w + col]);
}

void	set_image_color(t_image *img, int row, int col, unsigned int color)
{
	((unsigned int *)img->addr)[row * img->w + col] = color;
}
