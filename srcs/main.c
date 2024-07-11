#include "cub3D.h"

void init_crowbar_animation(t_data *game)
{
	int i;
	t_image *img;
	char path[32];

	i = 1;
	while (i < 14)
	{
	    img = gc_malloc(sizeof(t_image), &game->gc);
	    snprintf(path, sizeof(path), "textures/crowbar/attack%d.xpm", i);
	    img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->w, &img->h);
	    img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, &img->endian);
	    ft_lstadd_back(&game->crowbar_animation, ft_lstnew_gc(img, &game->gc));
	    i++;
	}
	ft_lstlast(game->crowbar_animation)->next = game->crowbar_animation;
	game->crowbar_animation_head = game->crowbar_animation;
	
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
	init_crowbar_animation(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_W, WIN_H, "cub3D");
	hook(&game);
	mlx_loop(game.mlx_ptr);
	return (0);	
}
