#include "cub3D.h"

// TODO: update file extension
static char	*get_texture_path(t_data *game, char *line)
{
	char	*path;
	int		fd;

	path = ft_strtrim_gc(line, "\n", &game->gc);
	if (ft_isvalid_extension(path, ".xpm") != 0)
		exit(gc_free(game->gc, "Error: invalid file extension\n", 2));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	close(fd);
	gc_free_ptr(&game->gc, path);
	game->elem_n++;
	return (path);
}

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
		if (value < 0 || value > 255 || (i == 2 && line_split[i + 1]))
			exit(gc_free(game->gc, "Error: invalid rgb color\n", 2));
		color |= value << ((2 - i++) * 8);
	}
	game->elem_n++;
	gc_free_ptr(&game->gc, line_trim);
	gc_free_ptr(&game->gc, line_split);
	return (color);
}

static void	set_elements(t_data *game, char *line)
{
	char	**line_split;

	line_split = ft_split_gc(line, ' ', &game->gc);
	if (ft_strcmp(line_split[0], "NO") == 0 && line_split[1])
		game->path_no = get_texture_path(game, line_split[1]);
	else if (ft_strcmp(line_split[0], "SO") == 0 && line_split[1])
		game->path_so = get_texture_path(game, line_split[1]);
	else if (ft_strcmp(line_split[0], "EA") == 0 && line_split[1])
		game->path_ea = get_texture_path(game, line_split[1]);
	else if (ft_strcmp(line_split[0], "WE") == 0 && line_split[1])
		game->path_we = get_texture_path(game, line_split[1]);
	else if (ft_strcmp(line_split[0], "F") == 0 && line_split[1])
		game->floor_color = get_color(game, line_split[1]);
	else if (ft_strcmp(line_split[0], "C") == 0 && line_split[1])
		game->ceiling_color = get_color(game, line_split[1]);
	gc_free_ptr(&game->gc, line_split);
}

int	parse_element(t_data *game, char *filename)
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
		if (game->map_index != -1)
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
	return (0);
}
