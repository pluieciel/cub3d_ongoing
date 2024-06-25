#include "cub3D.h"

int	main(int ac, char *av[])
{
    t_data	game;

    init(&game);
    if (ac != 2)
        exit(gc_free(game.gc, "Error: invalid argument\n", 2));
    parse_map(&game, av[1]);
    if (check_map(&game))
        exit(gc_free(game.gc, "Error: invalid map\n", 2));
    hook(&game);
    mlx_loop(game.mlx_ptr);
    mlx_destroy_display(game.mlx_ptr);
    gc_free(game.gc, "", 1);
    return (0);
}