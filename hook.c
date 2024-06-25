/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuzhao <yuzhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:17:45 by yuzhao            #+#    #+#             */
/*   Updated: 2024/06/25 09:54:06 by yuzhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_no_event(void *data)
{
	if (data)
	{
	}
	return (0);
}

int	close_window(t_data *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	game->win_ptr = NULL;
	return (0);
}

int	handle_keypress(int keysym, t_data *game)
{
	if (keysym == XK_Escape)
		close_window(game);
	else if (keysym == 119)
		game->key.w = 1;
	else if (keysym == 97)
		game->key.a = 1;
	else if (keysym == 115)
		game->key.s = 1;
	else if (keysym == 100)
		game->key.d = 1;
	else if (keysym == 65361)
		game->key.left = 1;
	else if (keysym == 65363)
		game->key.right = 1;
	else if (keysym == 65362)
		game->key.up = 1;
	else if (keysym == 65364)
		game->key.down = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_data *game)
{
	if (keysym == 119)
		game->key.w = 0;
	else if (keysym == 97)
		game->key.a = 0;
	else if (keysym == 115)
		game->key.s = 0;
	else if (keysym == 100)
		game->key.d = 0;
	else if (keysym == 65361)
		game->key.left = 0;
	else if (keysym == 65363)
		game->key.right = 0;
	else if (keysym == 65362)
		game->key.up = 0;
	else if (keysym == 65364)
		game->key.down = 0;
	return (0);
}

int	render(t_data *game)
{
	(void)game;
	return (0);
}

void	hook(t_data *game)
{
	mlx_loop_hook(game->mlx_ptr, &render, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->win_ptr, 17, 0, &close_window, game);
}
