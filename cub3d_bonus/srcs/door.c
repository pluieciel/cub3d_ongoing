/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <jlefonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:02 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/22 09:24:30 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	add_new_door(t_data *game)
{
	t_door	*new;

	game->coll_door_h = 0;
	game->coll_door_v = 0;
	check_collision(game, game->player.dir_x, game->player.dir_y, OPEN_DIS);
	if ((game->coll_door_h || game->coll_door_v)
		&& (game->map[(int)game->rc->map_y][(int)game->rc->map_x] == 2
		|| game->map[(int)game->rc->map_y][(int)game->rc->map_x] == 3))
	{
		new = gc_malloc(sizeof(t_door), &game->gc);
		new->next = game->doors;
		new->x = (int)game->rc->map_x;
		new->y = (int)game->rc->map_y;
		new->closed = (game->map[new->y][new->x] == 3);
		game->doors = new;
	}
}

static void	remove_door(t_data *game)
{
	t_door	*temp;
	t_door	*prev;

	temp = game->doors;
	prev = NULL;
	while (temp && (game->map[temp->y][temp->x] <= 2
		|| game->map[temp->y][temp->x] >= 3))
	{
		game->doors = temp->next;
		temp = game->doors;
	}
	while (temp)
	{
		while (temp && (game->map[temp->y][temp->x] != 2
			&& game->map[temp->y][temp->x] != 3))
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
			return ;
		prev->next = temp->next;
		temp = prev->next;
	}
}

void	update_doors(t_data *game)
{
	t_door	*temp;

	if (game->key.e == 1)
		add_new_door(game);
	game->key.e = 0;
	temp = game->doors;
	while (temp)
	{
		game->map[temp->y][temp->x] += ((temp->closed) * (-2) + 1) * 0.1;
		if (game->map[temp->y][temp->x] <= 2)
			game->map[temp->y][temp->x] = 2;
		else if (game->map[temp->y][temp->x] >= 3)
			game->map[temp->y][temp->x] = 3;
		temp = temp->next;
	}
	remove_door(game);
}
