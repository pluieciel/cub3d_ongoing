/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:01 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/20 23:58:19 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_player(t_data *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.z = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.dir3d.x = 0;
	game->player.dir3d.y = 0;
	game->player.dir3d.z = 0;
}

static void	init_keys(t_data *game)
{
	game->key.w = 0;
	game->key.a = 0;
	game->key.s = 0;
	game->key.d = 0;
	game->key.left = 0;
	game->key.right = 0;
	game->key.up = 0;
	game->key.down = 0;
}

static void	init_images_walls(t_data *game)
{
	game->img_wall_no.w = 0;
	game->img_wall_no.h = 0;
	game->img_wall_no.ptr = NULL;
	game->img_wall_no.addr = NULL;
	game->img_wall_so.w = 0;
	game->img_wall_so.h = 0;
	game->img_wall_so.ptr = NULL;
	game->img_wall_so.addr = NULL;
	game->img_wall_ea.w = 0;
	game->img_wall_ea.h = 0;
	game->img_wall_ea.ptr = NULL;
	game->img_wall_ea.addr = NULL;
	game->img_wall_we.w = 0;
	game->img_wall_we.h = 0;
	game->img_wall_we.ptr = NULL;
	game->img_wall_we.addr = NULL;
}

static void	init_images(t_data *game)
{
	init_images_walls(game);
	game->img.w = WIN_W;
	game->img.h = WIN_H;
	game->img.ptr = mlx_new_image(game->mlx_ptr, game->img.w, game->img.h);
	game->img.addr = mlx_get_data_addr(game->img.ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
}

void	init(t_data *game)
{
	game->gc = NULL;
	game->win_ptr = NULL;
	game->mlx_ptr = NULL;
	game->elem_n = 0;
	game->map_index = -1;
	game->map_h = 0;
	game->map_w = 0;
	game->dis_p_s = DIS_P_S;
	game->time = get_timestamp_ms();
	game->mlx_ptr = mlx_init();
	game->gc = (t_gc *)gc_insert(game->gc, game->mlx_ptr);
	game->timestep = 1000 / FPS;
	init_images(game);
	init_player(game);
	init_keys(game);
}
