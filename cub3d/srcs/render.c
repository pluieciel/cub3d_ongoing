/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:55 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 00:38:02 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render(t_data *game)
{
	__uint64_t			current_time;

	current_time = get_timestamp_ms();
	if (game->win_ptr != NULL && (current_time - game->time) > 1000 / FPS)
	{
		game->time = current_time;
		ft_bzero(game->img.addr, game->img.w * game->img.h * (game->img.bpp / 8));
		update_player(game);
		draw_textures(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.ptr, 0, 0);
	}
	return (0);
}
