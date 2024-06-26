#include "cub3D.h"

int parse_element(t_data *game, char *filename)
{
	int fd;
	char *line;
	char **line_split;
	int i;
	int start = -1;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	line = get_next_line(fd);
	game->gc = gc_insert(game->gc, line);
	i = 0;
	while (line)
	{
		line_split = ft_split_gc(line, ' ', &game->gc);
		if (ft_strcmp(line_split[0], "NO") == 0)
			printf("test\n");
		gc_free_ptr(&game->gc, line_split);
		line = get_next_line(fd);
		game->gc = gc_insert(game->gc, line);
	}
	ft_printf("%d\n", start);
	ft_printf("%d\n", game->map_h);
	return (start);
}
