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
#include <pthread.h>

#define ASPECT_RATIO (16.0 / 8.0)
#define WIN_W 1280
#define WIN_H (WIN_W / ASPECT_RATIO)
#define FPS 60
#define B_SIZE 64
#define ROT_SPEED 0.1
#define MM_FACTOR 4
#define MM_RADIUS 100
#define MM_POS_X (MM_RADIUS + 20)
#define MM_POS_Y (WIN_H - MM_RADIUS - 20)
#define MM_RANGE 8
#define DIS_P_S (WIN_W / 2)
#define RAYCAST_RANGE 20
#define ELEM_N 7
#define COLL_DIS 20
#define OPEN_DIS 80
#define MOVE_SPEED 4
#define M_PI 3.14159265358979323846
#define NUM_THREADS 8
#define TRANSPARENT_COLOR 0xFF000000
#define MOUSE_THRESHOLD 4

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

typedef struct s_point3D
{
    float x;
    float y;
    float z;
    float angle;
} t_point3D;

typedef struct s_player
{
	int			pos[2];
	float		dir[2];
	t_point3D	dir3D;
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

typedef struct s_image
{
	void		*ptr;
	char		*addr;
	int			h;
	int			w;
	int			bpp;
	int			endian;
	int			line_len;
}				t_image;

typedef struct s_door
{
	int				x;
	int				y;
	int				open_close; // 0:to open, 1:to close
	struct s_door	*next;
}				t_door;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	float		**map;
	char		**visited;
	t_list		*crowbar_animation;
	t_list 		*crowbar_animation_head;
	int			map_w;
	int			map_h;
	int			map_index;
	int			floor_color;
	int			ceiling_color;
	int			elem_n;
	t_player	player;
	t_key		key;
	t_gc		*gc;
	long long	time;
	t_image		img;
	int			dis_p_s;
	int left_click;
	// 0 1 -> x y
	// 2 -> dis
	// 3 -> dir
	// 4 5 x y idx on map
	float		res_rc_h[6];
	float		res_rc_v[6];
	float		*res_rc;
	t_image		img_sky;
	t_image		img_wall_no;
	t_image		img_wall_so;
	t_image		img_wall_ea;
	t_image		img_wall_we;
	t_image		img_floor;
	t_image		img_door;
	int			op_door;
	t_door		*doors;
	int 		coll_h;
	int 		coll_v;
	int 		coll_door_h;
	int 		coll_door_v;
	int mouse_centered;
	long long crowbar_animation_time;
}				t_data;

typedef struct s_raycast
{
	pthread_t	tid;
	t_data		*game;
	t_point3D	*p1, *p2;
	int			col_start;
    int			col_end;
	float		temp[3];
	// x y z dis dir idx_x idx_y
	float		res_rc_h_3D[7];
	float		res_rc_v_3D[7];
	float		*res_rc_3D;
	// x y z dis dir
	int			num_doors_h;
	int			num_doors_v;
	float		doors_h[20][7];
	float		doors_v[20][7];
	float		nearest_wall_dis;
	
}				t_raycast;

void		init(t_data *game);
void		parse_map(t_data *game, char *filename);
void		hook(t_data *game);
int			check_map(t_data *game);
long long	millitimestamp(void);
int			render(t_data *game);
void		parse_element(t_data *game, char *filename);
float		distance(float x1, float y1, float x2, float y2);
float		raycast_h(t_data *game, float x, float y, int type);
float		raycast_v(t_data *game, float x, float y, int type);
void		raycast(t_data *game, float x, float y, int type);
void		ft_bresenham(t_point a, t_point b, t_image *img);
t_point3D	*ro_on_z_to_xz(t_point3D p);
t_point3D	*ro_on_y(t_point3D p, float angle_z);
t_point3D	*ro_back_on_z(t_point3D p);
t_point3D	*cross(t_point3D p1, t_point3D p2);
void		raycast_3D(t_raycast *ray);
