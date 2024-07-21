/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:10:07 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 15:16:09 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_on_error(t_data *game, char *error_msg)
{
	destroy_images(game);
	mlx_destroy_display(game->mlx_ptr);
	exit(gc_free(game->gc, error_msg, 2));
}

int	close_window(t_data *game)
{
	destroy_images(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	gc_free(game->gc, "", 1);
	exit(EXIT_SUCCESS);
}

void	check_file(t_data *game, char *path, char *ext)
{
	int	fd;

	if (ft_isvalid_extension(path, ext) != 0)
		exit_on_error(game, "Error: invalid file extension\n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_on_error(game, "Error: invalid file\n");
	close(fd);
}

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}
