#include "cub3d.h"

static void	apply_color_shading(t_data *game, t_image *img)
{
    int i;
    int j;
	unsigned int t;
	t_color color;
	t_color new;
    
    i = 0;
    while (i < img->w)
    {
        j = 0;
        while (j < img->h)
        {
			t = get_image_color(img, j, i);
            if (t != TRANSPARENT_COLOR)
			{              
			  	color = int_to_rgb(game->hud_color);
				shade_color(&color, t & 0xFF);
				set_rgb(color.r / 255, color.g / 255, color.b / 255, &new);
				set_image_color(img, j, i, rgb_to_int(new));
			}
			j++;
		}
		i++;
	}
}

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
