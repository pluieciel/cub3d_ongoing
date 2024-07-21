/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:05 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 14:04:41 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_data	game;

	init(&game);
	if (ac != 2)
		exit_on_error(&game, "Error: invalid argument\n");
	if (ft_isvalid_extension(av[1], ".cub") != 0)
		exit_on_error(&game, "Error: invalid file extension\n");
	parse_map(&game, av[1]);
	if (!isvalid_map(&game))
		exit_on_error(&game, "Error: invalid map\n");
	init_animations(&game);
	init_hud(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr, WIN_W, WIN_H, "cub3D");
	hook(&game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
