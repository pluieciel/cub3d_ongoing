#include "cub3D.h"

void	get_init_pos(t_data *game, char dir, int i, int j)
{
	if (game->player.dir[0] != 0 || game->player.dir[1] != 0)
		exit(gc_free(game->gc, "Error: multiple player position\n", 2));
	game->map[i][j] = 0;
	game->player.pos[0] = j * 64 + 32;
	game->player.pos[1] = i * 64 + 32;
	if (dir == 'N')
		game->player.dir[1] = -1 * 64;
	else if (dir == 'E')
		game->player.dir[0] = 1 * 64;
	else if (dir == 'S')
		game->player.dir[1] = 1 * 64;
	else if (dir == 'W')
		game->player.dir[0] = -1 * 64;
}

void	parse_map(t_data *game, char *filename)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	/*parse NO ./path_to_the_north_texture
	SO ./path_to_the_south_texture
	WE ./path_to_the_west_texture
	EA ./path_to_the_east_texture
	F 220,100,0
	C 225,30,0*/
	for (int k = 0; k < 6; k++)
	{
		line = get_next_line(fd);
		game->gc = gc_insert(game->gc, line);
	}
	line = get_next_line(fd);
	game->gc = gc_insert(game->gc, line);
	game->map_h = 20; // temp
	game->map_w = 40; // temp
	game->map = gc_malloc(sizeof(int *) * game->map_h, &game->gc);
	game->visited = gc_malloc(sizeof(int *) * game->map_h, &game->gc);
	i = -1;
	while (++i < game->map_h)
	{
		game->map[i] = gc_malloc(sizeof(int) * game->map_w, &game->gc);
		game->visited[i] = gc_malloc(sizeof(int) * game->map_w, &game->gc);
		j = -1;
		while (++j < game->map_w)
		{
			game->map[i][j] = -1;
			game->visited[i][j] = 0;
		}
	}
	i = 0;
	while (line)
	{
		j = 0;
		while (line[j])
		{
			if (line[j] == '1')
				game->map[i][j] = 1;
			else if (line[j] == '0')
				game->map[i][j] = 0;
			else if (line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
				|| line[j] == 'E')
				get_init_pos(game, line[j], i, j);
			else if (line[j] == ' ' || line[j] == '\t' || line[j] == '\n')
				;
			else
				exit(gc_free(game->gc, "Error: invalid char in map\n", 2));
			j++;
		}
		i++;
		line = get_next_line(fd);
		game->gc = gc_insert(game->gc, line);
	}
}
