#include "../includes/cub3d.h"

static void	init_animation(t_data *game, struct s_animation *animation,
		char *state, int frames)
{
	int		i;
	int		fd;
	t_image	*img;
	char	path[48];

	i = 1;
	while (i <= frames)
	{
		img = gc_malloc(sizeof(t_image), &game->gc);
		snprintf(path, sizeof(path), "resources/%s%d.xpm", state, i);
		fd = open(path, O_RDONLY);
		if (fd < 0)
			exit(gc_free(game->gc, "Error: invalid file\n", 2));
		close(fd);
		img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->w, &img->h);
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len,
				&img->endian);
		ft_lstadd_back(&animation->frames, ft_lstnew_gc(img, &game->gc));
		i++;
	}
	ft_lstlast(animation->frames)->next = animation->frames;
	animation->head = animation->frames;
}

void	init_crowbar(t_data *game)
{
	game->crowbar.draw.frames = NULL;
	game->crowbar.draw.head = NULL;
	game->crowbar.attack.frames = NULL;
	game->crowbar.attack.head = NULL;
	game->crowbar.attack_hit.frames = NULL;
	game->crowbar.attack_hit.head = NULL;
	game->crowbar.holster.frames = NULL;
	game->crowbar.holster.head = NULL;
	game->crowbar.state = CROWBAR_DRAW;
	game->crowbar.equiped = 0;
	game->crowbar.completed = 0;
	init_animation(game, &game->crowbar.draw, "crowbar/draw", 12);
	init_animation(game, &game->crowbar.attack, "crowbar/attack", 13);
	init_animation(game, &game->crowbar.attack_hit, "crowbar/attack_hit", 13);
	init_animation(game, &game->crowbar.holster, "crowbar/holster", 12);
}

void	init_handgun(t_data *game)
{
	game->handgun.draw.frames = NULL;
	game->handgun.draw.head = NULL;
	game->handgun.shoot.frames = NULL;
	game->handgun.shoot.head = NULL;
	game->handgun.holster.frames = NULL;
	game->handgun.holster.head = NULL;
	game->handgun.state = HANDGUN_NONE;
	game->handgun.equiped = 0;
	game->handgun.completed = 0;
	init_animation(game, &game->handgun.draw, "handgun/draw", 15);
	init_animation(game, &game->handgun.shoot, "handgun/shoot", 14);
	init_animation(game, &game->handgun.holster, "handgun/holster", 15);
}
