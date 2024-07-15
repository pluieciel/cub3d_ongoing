#include "cub3d.h"

void	get_init_pos(t_data *game, char dir, int i, int j)
{
	float	oldDirX;
	float	oldDirY;
	float	oldDirX_3d;
	float	oldDirY_3d;

	if (game->player.dir[0] != 0 || game->player.dir[1] != 0)
		exit(gc_free(game->gc, "Error: multiple player position\n", 2));
	game->map[i][j] = 0;
	game->player.pos[0] = j * B_SIZE + B_SIZE / 2;
	game->player.pos[1] = i * B_SIZE + B_SIZE / 2;
	if (dir == 'N')
	{
		game->player.dir[1] = -1;
		game->player.dir3d.y = -1;
	}
	else if (dir == 'E')
	{
		game->player.dir[0] = 1;
		game->player.dir3d.x = 1;
	}
	else if (dir == 'S')
	{
		game->player.dir[1] = 1;
		game->player.dir3d.y = 1;
	}
	else if (dir == 'W')
	{
		game->player.dir[0] = -1;
		game->player.dir3d.x = -1;
	}
	oldDirX = game->player.dir[0];
	oldDirY = game->player.dir[1];
	oldDirX_3d = game->player.dir3d.x;
	oldDirY_3d = game->player.dir3d.y;
	game->player.dir[0] = oldDirX * cos(-ROT_SPEED) - oldDirY
		* sin(-ROT_SPEED);
	game->player.dir[1] = oldDirX * sin(-ROT_SPEED) + oldDirY
		* cos(-ROT_SPEED);
	game->player.dir3d.x = oldDirX_3d * cos(-ROT_SPEED) - oldDirY_3d
		* sin(-ROT_SPEED);
	game->player.dir3d.y = oldDirX_3d * sin(-ROT_SPEED) + oldDirY_3d
		* cos(-ROT_SPEED);
	get_vector_right(game, &game->player.v_right);
	get_vector_down(game, &game->player.v_right, &game->player.v_down);
	//printv(game->player.dir3d);
	//printv(game->player.v_right);
	//printv(game->player.v_down);
}

void	parse_map(t_data *game, char *filename)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	parse_element(game, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	for (int k = 0; k < game->map_index; k++)
	{
		line = get_next_line(fd);
		game->gc = gc_insert(game->gc, line);
	}
	line = get_next_line(fd);
	game->gc = gc_insert(game->gc, line);
	game->map = gc_malloc(sizeof(float *) * game->map_h, &game->gc);
	game->visited = gc_malloc(sizeof(int *) * game->map_h, &game->gc);
	i = -1;
	while (++i < game->map_h)
	{
		game->map[i] = gc_malloc(sizeof(float) * game->map_w, &game->gc);
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
			else if (line[j] == '2')
				game->map[i][j] = 2;
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
