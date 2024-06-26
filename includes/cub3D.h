#pragma once

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include "../libft_gc/includes/libft_gc.h"
# include <X11/X.h>
# include <sys/time.h>

# define WIN_W 1280
# define WIN_H 768
# define MAP_W 1024
# define MAP_H 1024
# define FPS 20
# define ELEM_N 6

typedef struct s_player
{
	int		pos[2];
	int		dir[2];
}	t_player;

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	up;
	int	down;
}	t_key;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			map_w;
	int			map_h;
	int			map[MAP_W][MAP_H]; // put error if over size
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	int			floor_color;
	int			ceiling_color;
	int			elem_n;
	t_player	player;
	t_key		key;
	t_gc		*gc;
	long long	time;
}	t_data;

void	init(t_data *game);
void	parse_map(t_data *game, char *filename);
void	hook(t_data *game);

void		init(t_data *game);
void		parse_map(t_data *game, char *filename);
void		hook(t_data *game);
int			check_map(t_data *game);
long long	millitimestamp(void);
int			render(t_data *game);
int parse_element(t_data *game, char *filename);
