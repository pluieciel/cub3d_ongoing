#include "cub3d.h"

void	handle_mousethreshold(int dx, int dy, t_data *game)
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

int	handle_mousemove(int x, int y, t_data *game)
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
	handle_mousethreshold(dx, dy, game);
	game->mouse_centered = 1;
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}

int	handle_mouseclick(int button, int x, int y, t_data *game)
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
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, &close_window,
		game);
	mlx_hook(game->win_ptr, MotionNotify, PointerMotionMask, &handle_mousemove,
		game);
	mlx_mouse_hook(game->win_ptr, &handle_mouseclick, game);
}
