#include "cub3d.h"

void	destroy_imgs(t_data *game)
{
	// TODO: destroy animation images
	mlx_destroy_image(game->mlx_ptr, game->img_sky.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_no.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_so.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_ea.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_we.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_floor.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_door.ptr);
}

int close_window(t_data *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	game->win_ptr = NULL;
	if (game->img.ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->img.ptr);
	destroy_imgs(game);
	mlx_destroy_display(game->mlx_ptr);
	gc_free(game->gc, "", 1);
	exit(EXIT_SUCCESS);
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
	else if (key == XK_KP_Add && game->dis_p_s < 1500)
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

int handle_mousemove(int x, int y, t_data *game)
{
	if (game->mouse_centered)
	{
		game->mouse_centered = 0;
		return (0);
	}
    int dX;
    int dY;
	
	dX = x - (WIN_W / 2);
	dY = y - (WIN_H / 2);
    if (dX > MOUSE_THRESHOLD)
        game->key.right = 1;
    else if (dX < -MOUSE_THRESHOLD)
        game->key.left = 1;
    else
    {
        game->key.right = 0;
        game->key.left = 0;
    }
    if (dY > MOUSE_THRESHOLD)
        game->key.down = 1;
    else if (dY < -MOUSE_THRESHOLD)
        game->key.up = 1;
    else
    {
        game->key.down = 0;
        game->key.up = 0;
    }
	game->mouse_centered = 1;
    mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}

int handle_mouseclick(int button, int x, int y, t_data *game)
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
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, &close_window, game);
	mlx_hook(game->win_ptr, MotionNotify, PointerMotionMask, &handle_mousemove, game);
	mlx_mouse_hook(game->win_ptr, &handle_mouseclick, game);
}
