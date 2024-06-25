/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuzhao <yuzhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:17:45 by yuzhao            #+#    #+#             */
/*   Updated: 2024/06/25 09:17:13 by yuzhao           ###   ########.fr       */
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
		{game->key.w = 1}//doup(game);
	else if (keysym == 97)
		{}//doleft(game);
	else if (keysym == 115)
		{}//dodown(game);
	else if (keysym == 100)
		{}//doright(game);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	if (data || keysym)
	{
	}
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
	mlx_hook(game->win_ptr, 17, 0, &close_window, game);
}
