#include "cub3D.h"

static void	load_texture(t_data *game, t_image *img, char *line)
{
	char	*path;
	int		fd;

	if (img->ptr != NULL)
		exit(gc_free(game->gc, "Error: duplicated element\n", 2));
	path = ft_strtrim_gc(line, "\n", &game->gc);
	if (ft_isvalid_extension(path, ".xpm") != 0)
		exit(gc_free(game->gc, "Error: invalid file extension\n", 2));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	close(fd);
	img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->ptr,
			&img->bpp, &img->line_len, &img->endian);
	game->elem_n++;
}
// V1: only color
/*
static int	get_color(t_data *game, char *line)
{
	char	**line_split;
	char	*line_trim;
	int		i;
	int		value;
	int		color;

	line_trim = ft_strtrim_gc(line, "\n", &game->gc);
	line_split = ft_split_gc(line_trim, ',', &game->gc);
	color = 0;
	i = 0;
	while (line_split[i])
    {
        value = ft_atoi(line_split[i]);
        if (value < 0 || value > 255)
       		exit(gc_free(game->gc, "Error: invalid rgb color\n", 2));
        color |= value << ((2 - i) * 8);
        i++;
    }
	if (i != 3)
		exit(gc_free(game->gc, "Error: invalid rgb color\n", 2));
	game->elem_n++;
	gc_free_ptr(&game->gc, line_trim);
	gc_free_ptr(&game->gc, line_split);
	return (color);
}*/

static void	set_elements(t_data *game, char *line)
{
	char	**line_split;

	line_split = ft_split_gc(line, ' ', &game->gc);
	if (ft_strcmp(line_split[0], "NO") == 0 && line_split[1])
		load_texture(game, &game->img_wall_no, line_split[1]);
	else if (ft_strcmp(line_split[0], "SO") == 0 && line_split[1])
		load_texture(game, &game->img_wall_so, line_split[1]);
	else if (ft_strcmp(line_split[0], "EA") == 0 && line_split[1])
		load_texture(game, &game->img_wall_ea, line_split[1]);
	else if (ft_strcmp(line_split[0], "WE") == 0 && line_split[1])
		load_texture(game, &game->img_wall_we, line_split[1]);
	else if (ft_strcmp(line_split[0], "D") == 0 && line_split[1])
		load_texture(game, &game->img_door, line_split[1]);
	// V1: only color
	/*else if (ft_strcmp(line_split[0], "F") == 0 && line_split[1])
		game->floor_color = get_color(game, line_split[1]);
	else if (ft_strcmp(line_split[0], "C") == 0 && line_split[1])
		game->ceiling_color = get_color(game, line_split[1]);*/
	// V2: textures
	else if (ft_strcmp(line_split[0], "F") == 0 && line_split[1])
		load_texture(game, &game->img_floor, line_split[1]);
	else if (ft_strcmp(line_split[0], "C") == 0 && line_split[1])
		load_texture(game, &game->img_sky, line_split[1]);
	gc_free_ptr(&game->gc, line_split);
}

void parse_element(t_data *game, char *filename)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	line = get_next_line(fd);
	game->gc = gc_insert(game->gc, line);
	while (line)
	{
		set_elements(game, line);
		if (game->elem_n == ELEM_N && game->map_index == -1)
		{
			gc_free_ptr(&game->gc, line);
			line = get_next_line(fd);
			game->gc = gc_insert(game->gc, line);
			i++;
			while (line && line[0] == '\n')
			{
				gc_free_ptr(&game->gc, line);
				line = get_next_line(fd);
				game->gc = gc_insert(game->gc, line);
				i++;
			}
			game->map_index = i;
		}
		if (game->map_index != -1 && line != NULL)
		{
			game->map_h++;
			if ((int)(ft_strlen(line) - 1) > game->map_w)
				game->map_w = ft_strlen(line) - 1;
		}
		gc_free_ptr(&game->gc, line);
		line = get_next_line(fd);
		game->gc = gc_insert(game->gc, line);
		i++;
	}
	close(fd);
	if (game->elem_n != ELEM_N)
		exit(gc_free(game->gc, "Error: not enough elements\n", 2));
}
