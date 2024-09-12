/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <jlefonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:51 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/22 09:19:16 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_image(t_data *game, t_image *img, char *path)
{
	img->w = 0;
	img->h = 0;
	img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len,
			&img->endian);
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
	if (row >= 0 && row <= img->h && col >= 0 && col <= img->w)
		return (((unsigned int *)img->addr)[row * img->w + col]);
	return (0);
}

void	set_image_color(t_image *img, int row, int col, unsigned int color)
{
	if (row >= 0 && row <= img->h && col >= 0 && col <= img->w)
		((unsigned int *)img->addr)[row * img->w + col] = color;
}

void	destroy_images(t_data *game)
{
	if (game->img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.ptr);
	if (game->img_sky.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_sky.ptr);
	if (game->img_wall_no.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_wall_no.ptr);
	if (game->img_wall_so.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_wall_so.ptr);
	if (game->img_wall_ea.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_wall_ea.ptr);
	if (game->img_wall_we.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_wall_we.ptr);
	if (game->img_floor.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_floor.ptr);
	if (game->img_door.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_door.ptr);
}
