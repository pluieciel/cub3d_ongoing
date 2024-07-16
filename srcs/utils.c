#include "cub3d.h"

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

int	close_window(t_data *game)
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
