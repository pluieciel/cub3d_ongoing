#include "cub3D.h"

int	main(int ac, char *av[])
{
    t_data	game;

    if (ac != 2)
        exit(gc_free(game.gc, "Error: invalid argument\n", 2)
    init(&game);
    parse_map(&game, av[1]);
    printf("%d, %d\n", game.start_pos[0], game.start_pos[1]);
    //check map
    hook(&game);
    mlx_loop(game.mlx_ptr);
    mlx_destroy_display(game.mlx_ptr);
    gc_free(game.gc, "", 1);
    return (0);
}