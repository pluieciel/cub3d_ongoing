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
	mlx_destroy_image(game->mlx_ptr, game->img_sky.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_floor.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_door.img_ptr);
}

int close_window(t_data *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	game->win_ptr = NULL;
	if (game->img.img_ptr != NULL)
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
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
	//ft_printf("%d:%d\n", x, y);
	//mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W/2, WIN_H/2);
	(void)x;
	(void)y;
	float		oldDirX = game->player.dir[0];
	float		oldDirY = game->player.dir[1];
	float		oldDirX_3D = game->player.dir3D.x;
	float		oldDirY_3D = game->player.dir3D.y;
	game->player.dir[0] = oldDirX * cos(-ROT_SPEED) - oldDirY * sin(-ROT_SPEED);
	game->player.dir[1] = oldDirX * sin(-ROT_SPEED) + oldDirY * cos(-ROT_SPEED);
	game->player.dir3D.x = oldDirX_3D * cos(-ROT_SPEED) - oldDirY_3D * sin(-ROT_SPEED);
	game->player.dir3D.y = oldDirX_3D * sin(-ROT_SPEED) + oldDirY_3D * cos(-ROT_SPEED);
	if (game->player.dir[0] > 0)
		game->player.dir3D.angle = atan(game->player.dir[1] / game->player.dir[0]);
	else if (game->player.dir[0] < 0)
		game->player.dir3D.angle = atan(game->player.dir[1] / game->player.dir[0]) + M_PI;
	else
		game->player.dir3D.angle = ((game->player.dir[1] > 0) * 2 - 1) * M_PI / 2;
	return (0);
}

void	hook(t_data *game)
{
	mlx_loop_hook(game->mlx_ptr, &render, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, &close_window, game);
	mlx_hook(game->win_ptr, MotionNotify, PointerMotionMask, &mouse_move, game);
}
