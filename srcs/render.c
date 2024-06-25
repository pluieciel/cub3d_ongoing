#include "cub3D.h"

int	render(t_data *game)
{
	long long	now;
	long long	diff_millisecs;
	static int	x = 0;
	static int	y = 200;
	static int	color = 0x00FF00;

	now = millitimestamp();
	diff_millisecs = now - game->time;
	if (game->win_ptr != NULL && diff_millisecs > 1000 / FPS)
	{
		game->time = now;
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		//mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
		(((unsigned int *)game->img.addr)[y * WIN_W + x]) = color;
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.img_ptr, 0, 0);
		x++;
		if (x >= WIN_W)
			x = 0;
	}
	return (0);
}
