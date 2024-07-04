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
	game->mlx_ptr = mlx_init();
	game->gc = (t_gc *)gc_insert(game->gc, game->mlx_ptr);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_W, WIN_H, "cub3D");
	game->img.w = WIN_W;
	game->img.h = WIN_H;
	game->img.img_ptr = mlx_new_image(game->mlx_ptr,
			game->img.w, game->img.h);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	game->img_sky.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "textures/sky.xpm", &game->img_sky.w, &game->img_sky.h);
	game->img_sky.addr = mlx_get_data_addr(game->img_sky.img_ptr,
			&game->img_sky.bpp, &game->img_sky.line_len, &game->img_sky.endian);
	game->img_wall.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "textures/wall.xpm", &game->img_wall.w, &game->img_wall.h);
	game->img_wall.addr = mlx_get_data_addr(game->img_wall.img_ptr,
			&game->img_wall.bpp, &game->img_wall.line_len, &game->img_wall.endian);
	game->img_floor.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "textures/floor.xpm", &game->img_floor.w, &game->img_floor.h);
	game->img_floor.addr = mlx_get_data_addr(game->img_floor.img_ptr,
			&game->img_floor.bpp, &game->img_floor.line_len, &game->img_floor.endian);
	game->img_door.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "textures/door.xpm", &game->img_door.w, &game->img_door.h);
	game->img_door.addr = mlx_get_data_addr(game->img_door.img_ptr,
			&game->img_door.bpp, &game->img_door.line_len, &game->img_door.endian);
}
