/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <jlefonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:09:24 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/22 09:19:41 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_init_pos(t_data *game, char dir, int i, int j)
{
	float	olddirx;
	float	olddiry;
	float	olddirx_3d;
	float	olddiry_3d;

	if (game->player.dir_x != 0 || game->player.dir_y != 0)
		exit_on_error(game, "Error: multiple player position\n");
	game->map[i][j] = 0;
	game->player.x = j * B_SIZE + B_SIZE / 2;
	game->player.y = i * B_SIZE + B_SIZE / 2;
	set_dir(game, dir);
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

static void	handle_map_char(t_data *game, char *line, int i, int j)
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
		exit_on_error(game, "Error: invalid char in map\n");
}

static void	fill_map(t_data *game, int fd, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line)
	{
		j = 0;
		while (line[j])
		{
			handle_map_char(game, line, i, j);
			j++;
		}
		i++;
		line = get_next_line(fd, &game->gc);
	}
}

static void	init_map(t_data *game, int fd, char *line)
{
	int	i;
	int	j;

	line = get_next_line(fd, &game->gc);
	game->map = gc_malloc(sizeof(float *) * game->map_h, &game->gc);
	game->visited = gc_malloc(sizeof(int *) * game->map_h, &game->gc);
	i = -1;
	while (++(i) < game->map_h)
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
	fill_map(game, fd, line);
	close(fd);
}

void	parse_map(t_data *game, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	parse_elements(game, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_on_error(game, "Error: invalid file\n");
	i = -1;
	while (++i < game->map_index)
		line = get_next_line(fd, &game->gc);
	init_map(game, fd, line);
}
