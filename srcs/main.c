#include "cub3D.h"

void init2(t_data *game)
{
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
}

int	main(int ac, char *av[])
{
	t_data	game;

	init(&game);
	if (ac != 2)
		exit(gc_free(game.gc, "Error: invalid argument\n", 2));
	if (ft_isvalid_extension(av[1], ".cub") != 0)
		exit(gc_free(game.gc, "Error: invalid file extension\n", 2));
	parse_map(&game, av[1]);
	if (check_map(&game))
		exit(gc_free(game.gc, "Error: invalid map\n", 2));
	init2(&game);
	hook(&game);
	mlx_loop(game.mlx_ptr);
	gc_free(game.gc, "", 1);
	return (0);	
}
