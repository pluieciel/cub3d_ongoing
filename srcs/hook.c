#include "cub3D.h"

int	handle_no_event(void *data)
{
	if (data)
	{
	}
	return (0);
}

void	destroy_imgs(t_data *game)
{
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
	else if (keysym == 65451 && game->dis_p_s < 1500)
		game->dis_p_s += 300;
	else if (keysym == 65453 && game->dis_p_s > 400)
		game->dis_p_s -= 300;
	else if (keysym == 101 && game->op_door == 0)
		game->op_door = 1;
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

int mouse_move(int x, int y, t_data *game)
{
    int dX = x - (WIN_W / 2);
    int dY = y - (WIN_H / 2);

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

    mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}

void	hook(t_data *game)
{
    mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W / 2, WIN_H / 2);
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_loop_hook(game->mlx_ptr, &render, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, &close_window, game);
	mlx_hook(game->win_ptr, MotionNotify, PointerMotionMask, &mouse_move, game);
}
