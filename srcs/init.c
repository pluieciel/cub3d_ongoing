#include "cub3D.h"

void	init(t_data *game)
{
	int i;
	int j;

	i = -1;
	while (++i < MAP_H)
	{
		j = -1;
		while (++j < MAP_W)
			game->map[i][j] = -1;
	}
	game->gc = NULL;
	game->player.dir[0] = 0;
	game->player.dir[1] = 0;
	game->key.w = 0;
	game->key.a = 0;
	game->key.s = 0;
	game->key.d = 0;
	game->key.left = 0;
	game->key.right = 0;
	game->key.up = 0;
	game->key.down = 0;
	game->time = millitimestamp();
	game->mlx_ptr = mlx_init();
	game->gc = (t_gc *)gc_insert(game->gc, game->mlx_ptr);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_W, WIN_H, "cub3D");
}
