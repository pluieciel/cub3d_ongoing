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

#include <stdio.h>

int mouse_move(int x, int y, t_data *game)
{
	float rot_angle_x;
	if (x >=0 && x < WIN_W)
   		rot_angle_x = (x - (WIN_W / 2)) * 0.0005;
	float rot_angle_z;
	if (y >=0 && y < WIN_H)
    	rot_angle_z = ((WIN_H / 2) - y) * 0.0005;

    float oldDirX = game->player.dir[0];
    float oldDirY = game->player.dir[1];
	float oldDirX_3D = game->player.dir3D.x;
	float oldDirY_3D = game->player.dir3D.y;
    game->player.dir[0] = oldDirX * cos(rot_angle_x) - oldDirY * sin(rot_angle_x);
    game->player.dir[1] = oldDirX * sin(rot_angle_x) + oldDirY * cos(rot_angle_x);
	game->player.dir3D.x = oldDirX_3D * cos(rot_angle_x) - oldDirY_3D * sin(rot_angle_x);
    game->player.dir3D.y = oldDirX_3D * sin(rot_angle_x) + oldDirY_3D * cos(rot_angle_x);

	t_point3D	*p1;
	t_point3D	*p2;
	if (rot_angle_z != 0 && game->player.dir3D.z <= 0.95 && game->player.dir3D.z >= -0.95)
	{
		p1 = ro_on_z_to_xz(game->player.dir3D);
		p2 = ro_on_y(*p1, rot_angle_z);
		if (rot_angle_z != 0)
			printf("%f %f\n", p2->z, rot_angle_z);
		if (p2->z <= -0.95 || (rot_angle_z < 0 && p2->z > game->player.dir3D.z))
		{
			free(p2);
			p2 = ro_on_y(*p1, -rot_angle_z);
		}
		else if (p2->z >= 0.95 || (rot_angle_z > 0 && p2->z < game->player.dir3D.z))
		{
			free(p2);
			p2 = ro_on_y(*p1, -rot_angle_z);
		}
		free(p1);
		p1 = ro_back_on_z(*p2);
		free(p2);
		game->player.dir3D.x = p1->x;
		game->player.dir3D.y = p1->y;
		game->player.dir3D.z = p1->z;
		if (rot_angle_z != 0) printf("%f\n", game->player.dir3D.z);
		free(p1);
	}
	else if (rot_angle_z != 0 && game->player.dir3D.z > 0.95)
		game->player.dir3D.z = 0.95;
	else if (rot_angle_z != 0)
		game->player.dir3D.z = -0.95;
	if (game->player.dir[0] > 0)
		game->player.dir3D.angle = atan(game->player.dir[1] / game->player.dir[0]);
	else if (game->player.dir[0] < 0)
		game->player.dir3D.angle = atan(game->player.dir[1] / game->player.dir[0]) + M_PI;
	else
		game->player.dir3D.angle = ((game->player.dir[1] > 0) * 2 - 1) * M_PI / 2;
    mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIN_W / 2, WIN_H / 2);
	return (0);
}

void	hook(t_data *game)
{
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_loop_hook(game->mlx_ptr, &render, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
		game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, &close_window, game);
	mlx_hook(game->win_ptr, MotionNotify, PointerMotionMask, &mouse_move, game);
}
