/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:39 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 17:22:28 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_mouse_threshold(int dx, int dy, t_data *game)
{
	if (dx > MOUSE_THRESHOLD)
		game->key.right = 1;
	else if (dx < -MOUSE_THRESHOLD)
		game->key.left = 1;
	else
	{
		game->key.right = 0;
		game->key.left = 0;
	}
	if (dy > MOUSE_THRESHOLD)
		game->key.down = 1;
	else if (dy < -MOUSE_THRESHOLD)
		game->key.up = 1;
	else
	{
		game->key.down = 0;
		game->key.up = 0;
	}
}

static int	handle_mouse_move(int x, int y, t_data *game)
{
	int	dx;
	int	dy;

	if (game->mouse_centered)
	{
		game->mouse_centered = 0;
		return (0);
	}
	dx = x - (WIN_W / 2);
	dy = y - (WIN_H / 2);
	handle_mouse_threshold(dx, dy, game);
	game->mouse_centered = 1;
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}

static int	handle_mouse_click(int button, int x, int y, t_data *game)
{
	(void)x;
	(void)y;
	if (button == Button1)
		game->left_click = 1;
	else if (button == Button4 && game->dis_p_s < 1500)
		game->dis_p_s += 10;
	else if (button == Button5 && game->dis_p_s > 400)
		game->dis_p_s -= 10;
	return (0);
}

void	hook(t_data *game)
{
	game->mouse_centered = 1;
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W / 2, WIN_H / 2);
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_loop_hook(game->mlx_ptr, &render, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_key_press, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &handle_key_release,
		game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, &close_window,
		game);
	mlx_hook(game->win_ptr, MotionNotify, PointerMotionMask, &handle_mouse_move,
		game);
	mlx_mouse_hook(game->win_ptr, &handle_mouse_click, game);
}
