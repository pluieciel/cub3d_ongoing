/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:39 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 23:57:48 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	hook(t_data *game)
{
	mlx_loop_hook(game->mlx_ptr, &render, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_key_press, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &handle_key_release,
		game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, &close_window,
		game);
}
