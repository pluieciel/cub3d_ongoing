/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuzhao <yuzhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:27:41 by yuzhao            #+#    #+#             */
/*   Updated: 2024/06/25 11:34:09 by yuzhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	render(t_data *game)
{
	long long	now;
	long long	diff_millisecs;

	now = millitimestamp();
	diff_millisecs = now - game->time;
    static int x = 0;
    static int y = 0;
    static int color = 0x00FF00;
	if (game->win_ptr != NULL && diff_millisecs > 1000 / FPS)
	{
		game->time = now;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
        mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
        x++;
        if (x >= WIN_W)
            x = 0;
	}
	return (0);
}