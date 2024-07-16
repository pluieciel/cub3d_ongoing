#include "cub3d.h"

void	handle_specialkeys(int key, t_data *game)
{
	if (key == XK_KP_Add && game->dis_p_s < 1500)
		game->dis_p_s += 300;
	else if (key == XK_KP_Subtract && game->dis_p_s > 400)
		game->dis_p_s -= 300;
	else if (key == XK_e && game->op_door == 0)
		game->op_door = 1;
	else if (key == XK_1)
		game->key.one = 1;
	else if (key == XK_2)
		game->key.two = 1;
	else if (key == XK_Control_L)
		game->key.ctrl = 1;
	else if (key == XK_Shift_L)
		game->key.shift = 1;
	else if (key == XK_space)
		game->key.space = 1;
}

int	handle_keypress(int key, t_data *game)
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
	else
		handle_specialkeys(key, game);
	return (0);
}

int	handle_keyrelease(int key, t_data *game)
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
