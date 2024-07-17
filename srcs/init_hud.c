#include "cub3d.h"

void	init_hud(t_data *game)
{
	char			path[270];
	t_hud			*elem;
	DIR				*hud_dir;
	struct dirent	*dp;

	hud_dir = opendir("resources/hud");
	if (!hud_dir)
		exit(gc_free(game->gc, "Error\n Cannot open resources/hud", 2));
	dp = readdir(hud_dir);
	while (dp)
	{
		if (ft_strcmp(dp->d_name, ".") && ft_strcmp(dp->d_name, ".."))
		{
			elem = gc_malloc(sizeof(t_hud), &game->gc);
			snprintf(elem->name, sizeof(elem->name), "%s", dp->d_name);
			snprintf(path, sizeof(path), "resources/hud/%s", elem->name);
			check_file(game, path, ".xpm");
			set_image(game, &elem->img, path);
			apply_color_shading(game, elem->img);
			ft_lstadd_back(&game->hud_elem, ft_lstnew_gc(elem, &game->gc));
		}
		dp = readdir(hud_dir);
	}
	closedir(hud_dir);
}
