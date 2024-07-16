#include "cub3d.h"

int	check_pos(t_data *game, int x, int y, char **visited)
{
	//printf("x: %d, y: %d\n", x, y);
	if (x < 0 || y < 0 || x >= game->map_w || y >= game->map_h || game->map[y][x] == -1)
		return (1);
	if (visited[y][x] || game->map[y][x] > 0)
		return (0);
	visited[y][x] = 1;
	return (check_pos(game, x + 1, y, visited) || check_pos(game, x - 1, y,
			visited) || check_pos(game, x, y + 1, visited) || check_pos(game, x,
			y - 1, visited));
}

int	check_map(t_data *game)
{
	if (game->player.dir[0] == 0 && game->player.dir[1] == 0)
	{
		exit(gc_free(game->gc, "Error: no player position\n", 2));
	}
	return (check_pos(game, game->player.pos[0] / B_SIZE, game->player.pos[1] / B_SIZE, game->visited));
}
