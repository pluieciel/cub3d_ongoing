#include "cub3D.h"

int check_pos(t_data *game, int x, int y, int visited[MAP_H][MAP_W])
{
    if (x < 0 || y < 0 || x >= MAP_W || y >= MAP_H || game->map[y][x] == -1)
        return 1;
    if (visited[y][x] || game->map[y][x] == 1)
        return 0;
    visited[y][x] = 1;
    return (check_pos(game, x + 1, y, visited) || check_pos(game, x - 1, y, visited)
    || check_pos(game, x, y + 1, visited) || check_pos(game, x, y - 1, visited));
}

int	check_map(t_data *game)
{
    static int	visited[MAP_H][MAP_W];
    if (game->player.dir[0] == 0 && game->player.dir[1] == 0)
    {
        exit(gc_free(game->gc, "Error: no player position\n", 2));
    }
	return check_pos(game, game->player.pos[0], game->player.pos[1], visited);
}