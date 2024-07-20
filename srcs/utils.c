/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:10:07 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/19 23:01:20 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_imgs(t_data *game)
{
	t_hud	*hud;

	if (game->img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_sky.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_no.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_so.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_ea.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_we.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_floor.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_door.ptr);
	destroy_animations(game);
	while (game->hud_elem)
	{
		hud = (t_hud *)game->hud_elem->content;
		mlx_destroy_image(game->mlx_ptr, hud->img->ptr);
		game->hud_elem = game->hud_elem->next;
	}
}

int	close_window(t_data *game)
{
	destroy_imgs(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	gc_free(game->gc, "", 1);
	exit(EXIT_SUCCESS);
}

void	check_file(t_data *game, char *path, char *ext)
{
	int	fd;

	if (ft_isvalid_extension(path, ext) != 0)
		exit(gc_free(game->gc, "Error: invalid file extension\n", 2));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	close(fd);
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}
