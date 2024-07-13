#include "cub3d.h"

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
	init_crowbar(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_W, WIN_H, "cub3D");
	hook(&game);
	mlx_loop(game.mlx_ptr);
	return (0);	
}
