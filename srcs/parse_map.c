/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:24 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/18 15:09:24 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adddir(t_data *game, char dir)
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

void	get_init_pos(t_data *game, char dir, int i, int j)
{
	float	olddirx;
	float	olddiry;
	float	olddirx_3d;
	float	olddiry_3d;

	if (game->player.dir_x != 0 || game->player.dir_y != 0)
		exit(gc_free(game->gc, "Error: multiple player position\n", 2));
	game->map[i][j] = 0;
	game->player.x = j * B_SIZE + B_SIZE / 2;
	game->player.y = i * B_SIZE + B_SIZE / 2;
	adddir(game, dir);
	olddirx = game->player.dir_x;
	olddiry = game->player.dir_y;
	olddirx_3d = game->player.dir3d.x;
	olddiry_3d = game->player.dir3d.y;
	game->player.dir_x = olddirx * cos(-ROT_SPEED) - olddiry * sin(-ROT_SPEED);
	game->player.dir_y = olddirx * sin(-ROT_SPEED) + olddiry * cos(-ROT_SPEED);
	game->player.dir3d.x = olddirx_3d * cos(-ROT_SPEED) - olddiry_3d
		* sin(-ROT_SPEED);
	game->player.dir3d.y = olddirx_3d * sin(-ROT_SPEED) + olddiry_3d
		* cos(-ROT_SPEED);
	get_vector_right(game, &game->player.v_right);
	get_vector_down(game, &game->player.v_right, &game->player.v_down);
}

void	parse_map3(t_data *game, int fd, char *l, int *i)
{
	i[0] = 0;
	while (l)
	{
		i[1] = 0;
		while (l[i[1]])
		{
			if (l[i[1]] == '1')
				game->map[i[0]][i[1]] = 1;
			else if (l[i[1]] == '2')
				game->map[i[0]][i[1]] = 2;
			else if (l[i[1]] == '0')
				game->map[i[0]][i[1]] = 0;
			else if (l[i[1]] == 'N' || l[i[1]] == 'S' || l[i[1]] == 'W'
				|| l[i[1]] == 'E')
				get_init_pos(game, l[i[1]], i[0], i[1]);
			else if (l[i[1]] == ' ' || l[i[1]] == '\t' || l[i[1]] == '\n')
				;
			else
				exit(gc_free(game->gc, "Error: invalid char in map\n", 2));
			(i[1])++;
		}
		(i[0])++;
		l = get_next_line(fd);
		game->gc = gc_insert(game->gc, l);
	}
}

void	parse_map2(t_data *game, int fd, char *line)
{
	int		i[2];

	i[0] = -1;
	while (++(i[0]) < game->map_h)
	{
		game->map[i[0]] = gc_malloc(sizeof(float) * game->map_w, &game->gc);
		game->visited[i[0]] = gc_malloc(sizeof(int) * game->map_w, &game->gc);
		i[1] = -1;
		while (++(i[1]) < game->map_w)
		{
			game->map[i[0]][i[1]] = -1;
			game->visited[i[0]][i[1]] = 0;
		}
	}
	parse_map3(game, fd, line, i);
}

void	parse_map(t_data *game, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	parse_elements(game, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	i = -1;
	while (++i < game->map_index)
	{
		line = get_next_line(fd);
		game->gc = gc_insert(game->gc, line);
	}
	line = get_next_line(fd);
	game->gc = gc_insert(game->gc, line);
	game->map = gc_malloc(sizeof(float *) * game->map_h, &game->gc);
	game->visited = gc_malloc(sizeof(int *) * game->map_h, &game->gc);
	parse_map2(game, fd, line);
}
