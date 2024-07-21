/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:32 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 23:57:22 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_special_keys(int key, t_data *game)
{
	if (key == XK_KP_Add && game->dis_p_s < 1500)
		game->dis_p_s += 300;
	else if (key == XK_KP_Subtract && game->dis_p_s > 400)
		game->dis_p_s -= 300;
}

int	handle_key_press(int key, t_data *game)
{
	if (key == XK_Escape)
		close_window(game);
	else if (key == XK_w)
		game->key.w = 1;
	else if (key == XK_a)
		game->key.a = 1;
	else if (key == XK_s)
		game->key.s = 1;
	else if (key == XK_d)
		game->key.d = 1;
	else if (key == XK_Left)
		game->key.left = 1;
	else if (key == XK_Right)
		game->key.right = 1;
	else if (key == XK_Up)
		game->key.up = 1;
	else if (key == XK_Down)
		game->key.down = 1;
	return (0);
}

int	handle_key_release(int key, t_data *game)
{
	if (key == XK_w)
		game->key.w = 0;
	else if (key == XK_a)
		game->key.a = 0;
	else if (key == XK_s)
		game->key.s = 0;
	else if (key == XK_d)
		game->key.d = 0;
	else if (key == XK_Left)
		game->key.left = 0;
	else if (key == XK_Right)
		game->key.right = 0;
	else if (key == XK_Up)
		game->key.up = 0;
	else if (key == XK_Down)
		game->key.down = 0;
	return (0);
}
