#pragma once

#include "../libft_gc/includes/libft_gc.h"
#include "../minilibx/mlx.h"
#include "../minilibx/mlx_int.h"
#include <X11/X.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define WIN_W 1280
#define WIN_H WIN_W / 2
#define FPS 20
#define B_SIZE 64
#define ROT_SPEED 0.1
#define MM_FACTOR 2
#define MM_RADIUS 100
#define MM_POS_X (MM_RADIUS + 20)
#define MM_POS_Y (WIN_H - MM_RADIUS - 20)
#define MM_RANGE 4
#define DIS_P_S (WIN_W / 2)
#define RAYCAST_RANGE 20
#define ELEM_N 6
#define COLL_DIS 20
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

typedef struct s_point
{
	int			x;
	int			y;
	int			color;
}				t_point;

typedef struct s_delta
{
	int			dx;
	int			dy;
}				t_delta;

typedef struct s_player
{
	int			pos[2];
	float		dir[2];
}				t_player;

typedef struct s_key
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			up;
	int			down;
}				t_key;

typedef struct s_img1
{
	void		*img_ptr;
	char		*addr;
	int			h;
	int			w;
	int			bpp;
	int			endian;
	int			line_len;
}				t_img1;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	char		**visited;
	int			map_w;
	int			map_h;
	int			map_index;
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
	t_img1		img;
	// 0 1 -> x y
	// 2 -> dis
	// 3 -> dir
	float		res_rc_h[4];
	float		res_rc_v[4];
	float		*res_rc;
	int			bestColl;
}				t_data;

void		init(t_data *game);
void		parse_map(t_data *game, char *filename);
void		hook(t_data *game);
int			check_map(t_data *game);
long long	millitimestamp(void);
int			render(t_data *game);
void		parse_element(t_data *game, char *filename);
float		distance(float x1, float y1, float x2, float y2);
float		raycast_h(t_data *game, float x, float y);
float		raycast_v(t_data *game, float x, float y);
void		raycast(t_data *game, float x, float y);
void		ft_bresenham(t_point a, t_point b, t_img1 *img);
