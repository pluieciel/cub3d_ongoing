/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuzhao <yuzhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:47:38 by yuzhao            #+#    #+#             */
/*   Updated: 2024/06/24 16:26:23 by yuzhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "my_gc.h"
# include "get_next_line.h"
# include <X11/X.h>
# include <sys/time.h>

# define WIN_W 1280
# define WIN_H 768
# define MAP_W 1024
# define MAP_H 1024

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		map[MAP_W][MAP_H]; // put error if >1024
	int		start_pos[2];
	int		start_dir[2];
	t_gc	*gc;
}	t_data;

void	init(t_data *game);
void	parse_map(t_data *game, char *filename);
void	hook(t_data *game);