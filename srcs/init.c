#include "cub3D.h"

void	init(t_data *game)
{
	game->gc = NULL;
	game->win_ptr = NULL;
	game->mlx_ptr = NULL;
	game->player.pos[0] = 0;
	game->player.pos[1] = 0;
	game->player.dir[0] = 0;
	game->player.dir[1] = 0;
	game->player.dir3D.x = 0;
	game->player.dir3D.y = 0;
	game->player.dir3D.z = 0;
	game->player.dir3D.angle = 0;
	game->key.w = 0;
	game->key.a = 0;
	game->key.s = 0;
	game->key.d = 0;
	game->key.left = 0;
	game->key.right = 0;
	game->key.up = 0;
	game->key.down = 0;
	game->elem_n = 0;
	game->map_index = -1;
	game->map_h = 0;
	game->map_w = 0;
	game->dis_p_s = DIS_P_S;
	game->time = millitimestamp();
	game->op_door = 0;
	game->doors = NULL;
	game->mlx_ptr = mlx_init();
	game->gc = (t_gc *)gc_insert(game->gc, game->mlx_ptr);
}
