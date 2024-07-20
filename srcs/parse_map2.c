/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:50:35 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/18 15:54:02 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir(t_data *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir_y = -1;
		game->player.dir3d.y = -1;
	}
	else if (dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir3d.x = 1;
	}
	else if (dir == 'S')
	{
		game->player.dir_y = 1;
		game->player.dir3d.y = 1;
	}
	else if (dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir3d.x = -1;
	}
}
