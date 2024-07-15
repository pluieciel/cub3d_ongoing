#include "cub3D.h"

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
	init_handgun(&game);
	t_image *img = &game.img_hud_health;
	img->ptr = mlx_xpm_file_to_image(game.mlx_ptr, "textures/hud/hud_cross.xpm", &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, &img->endian);
	change_image_color(&game, img);
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_W, WIN_H, "cub3D");
	hook(&game);
	mlx_loop(game.mlx_ptr);
	return (0);	
}
