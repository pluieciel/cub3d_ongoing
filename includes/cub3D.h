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
# define MAP_W 50
# define MAP_H 50
# define FPS 20

typedef struct s_player
{
	int		pos[2];
	float	dir[2];
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

typedef struct s_img1
{
	void			*img_ptr;
	char			*addr;
	int				h;
	int				w;
	int				bpp;
	int				endian;
	int				line_len;
}	t_img1;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**visited;
	int			map_h;
	int			map_w;
	t_player	player;
	t_key		key;
	t_gc		*gc;
	long long	time;
	t_img1		img;
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
