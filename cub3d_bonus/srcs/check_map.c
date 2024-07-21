/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:07:41 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 17:22:28 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_pos(t_data *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_w || y >= game->map_h || game->map[y][x] == -1)
		return (0);
	if (game->visited[y][x] || game->map[y][x] == 1)
		return (1);
	game->visited[y][x] = 1;
	return (check_pos(game, x + 1, y) && check_pos(game, x - 1, y) && check_pos(game, x, y + 1) && check_pos(game, x, y - 1));
}

int	isvalid_map(t_data *game)
{
	if (game->player.dir_x == 0 && game->player.dir_y == 0)
		exit_on_error(game, "Error: no player position\n");
	return (check_pos(game, game->player.x / B_SIZE, game->player.y / B_SIZE));
}
