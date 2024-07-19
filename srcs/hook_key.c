/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:32 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/19 23:07:38 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_select_weapon_keys(t_data *game, int one, int two, int three)
{
	game->key.one = one;
	game->key.two = two;
	game->key.three = three;
}

void	handle_special_keys(int key, t_data *game)
{
	if (key == XK_KP_Add && game->dis_p_s < 1500)
		game->dis_p_s += 300;
	else if (key == XK_KP_Subtract && game->dis_p_s > 400)
		game->dis_p_s -= 300;
	else if (key == XK_1)
		set_select_weapon_keys(game, 1, 0, 0);
	else if (key == XK_2)
		set_select_weapon_keys(game, 0, 1, 0);
	else if (key == XK_3)
		set_select_weapon_keys(game, 0, 0, 1);
	else if (key == XK_Control_L && !game->key.shift)
		game->key.ctrl = 1;
	else if (key == XK_Shift_L && !game->key.ctrl && !game->key.space)
		game->key.shift = 1;
	else if (key == XK_space && !game->key.ctrl)
		game->key.space = 1;
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
	else if (key == XK_e && game->key.e == 0)
		game->key.e = 1;
	else if (key == XK_Left)
		game->key.left = 1;
	else if (key == XK_Right)
		game->key.right = 1;
	else if (key == XK_Up)
		game->key.up = 1;
	else if (key == XK_Down)
		game->key.down = 1;
	else
		handle_special_keys(key, game);
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
	else if (key == XK_Control_L)
		game->key.ctrl = 0;
	else if (key == XK_Shift_L)
		game->key.shift = 0;
	return (0);
}
