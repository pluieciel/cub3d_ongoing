/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:51 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/18 15:08:51 by jlefonde         ###   ########.fr       */
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

unsigned int	get_image_color(t_image *img, int row, int col)
{
	return (((unsigned int *)img->addr)[row * img->w + col]);
}

void	set_image_color(t_image *img, int row, int col, unsigned int color)
{
	((unsigned int *)img->addr)[row * img->w + col] = color;
}
