#ifndef CUB3D_H
# define CUB3D_H

# include "../libft_gc/includes/libft_gc.h"
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"
# include <X11/X.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ASPECT_RATIO (16.0 / 8.0)
# define WIN_W 1280
# define WIN_H (WIN_W / ASPECT_RATIO)
# define FPS 60
# define B_SIZE 64
# define ROT_SPEED 0.1
# define MM_FACTOR 16
# define MM_RADIUS 100
# define MM_POS_X (WIN_W - MM_RADIUS - 20)
# define MM_POS_Y (WIN_H - MM_RADIUS - 20)
# define MM_RANGE 8
# define DIS_P_S (WIN_W / 2)
# define RAYCAST_RANGE 20
# define ELEM_N 8
# define COLL_DIS 20
# define OPEN_DIS 80
# define SPEED 3
# define M_PI 3.14159265358979323846
# define NUM_THREADS 8
# define TRANSPARENT_COLOR 0xFF000000
# define MOUSE_THRESHOLD 4
# define GRAVITY 1500
# define JUMP_VELOCITY (GRAVITY / 6)

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;

typedef struct s_animation
{
	t_list			*frames;
	t_list			*head;
}					t_animation;

typedef struct s_crowbar
{
	enum			e_state_crowbar
	{
		CROWBAR_IDLE,
		CROWBAR_DRAW,
		CROWBAR_ATTACK,
		CROWBAR_ATTACK_HIT,
		CROWBAR_HOLSTER,
		CROWBAR_NONE
	} state;
	t_animation		draw;
	t_animation		attack;
	t_animation		attack_hit;
	t_animation		holster;
	int				equiped;
	int				completed;
}					t_crowbar;

typedef struct s_handgun
{
	enum			e_state_handgun
	{
		HANDGUN_IDLE,
		HANDGUN_DRAW,
		HANDGUN_SHOOT,
		HANDGUN_HOLSTER,
		HANDGUN_NONE
	} state;
	t_animation		draw;
	t_animation		shoot;
	t_animation		holster;
	int				equiped;
	int				completed;
}					t_handgun;

typedef struct s_point3d
{
	float			x;
	float			y;
	float			z;
}					t_point3d;

typedef struct s_player
{
	int				speed;
	int				x;
	int				y;
	float			z;
	float			dir_x;
	float			dir_y;
	float			jump_velocity;
	t_point3d		v_right;
	t_point3d		v_down;
	t_point3d		dir3d;
}					t_player;

typedef struct s_key
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				e;
	int				left;
	int				right;
	int				up;
	int				down;
	int				one;
	int				two;
	int				ctrl;
	int				shift;
	int				space;
}					t_key;

typedef struct s_image
{
	void			*ptr;
	char			*addr;
	int				h;
	int				w;
	int				bpp;
	int				endian;
	int				line_len;
}					t_image;

typedef struct s_hud
{
	t_image			*img;
	char			name[256];
}					t_hud;

typedef struct s_door
{
	int				x;
	int				y;
	int				closed;
	struct s_door	*next;
}					t_door;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			**visited;
	float			**map;
	float			*res_rc;
	//	0 1 -> x y
	//	2 -> dis
	//	3 -> dir
	//	4 5 x y idx on map
	float			res_rc_h[6];
	float			res_rc_v[6];
	int				map_w;
	int				map_h;
	int				map_index;
	int				elem_n;
	int				coll_wall_h;
	int				coll_wall_v;
	int				coll_door_h;
	int				coll_door_v;
	int				mouse_centered;
	int				left_click;
	int				dis_p_s;
	unsigned int	hud_color;
	t_player		player;
	t_key			key;
	t_gc			*gc;
	t_image			img;
	t_image			img_sky;
	t_image			img_wall_no;
	t_image			img_wall_so;
	t_image			img_wall_ea;
	t_image			img_wall_we;
	t_image			img_floor;
	t_image			img_door;
	t_list			*hud_elem;
	t_door			*doors;
	t_crowbar		crowbar;
	t_handgun		handgun;
	__uint64_t		time;
	__uint64_t		animation_time;
	__uint64_t		timestep;
}					t_data;

typedef struct s_raycast
{
	pthread_t		tid;
	t_data			*g;
	t_point3d		*p1;
	t_point3d		*p2;
	int				col_start;
	int				col_end;
	float			x;
	float			y;
	float			z;
	//	x y z dis dir idx_x idx_y
	float			h[7];
	float			v[7];
	float			*res_rc_3d;
	//	x y z dis dir
	int				num_doors_h;
	int				num_doors_v;
	float			doors_h[20][7];
	float			doors_v[20][7];
	float			nearest_wall_dis;
}					t_raycast;

void				init(t_data *game);
void				parse_map(t_data *game, char *filename);
void				hook(t_data *game);
int					isvalid_map(t_data *game);
__uint64_t			get_timestamp_ms(void);
int					render(t_data *game);
void				parse_elements(t_data *game, char *filename);
float				distance(float x1, float y1, float x2, float y2);
float				raycast_h(t_data *game, float x, float y, int type);
float				raycast_v(t_data *game, float x, float y, int type);
void				raycast(t_data *game, float x, float y, int type);
float				raycast_v_3d(t_raycast *r);
void				raycast_3d(t_raycast *ray);
void				update_crowbar_state(t_data *game);
void				update_handgun_state(t_data *game);
void				collision(t_data *game, float dir_x, float dir_y,
						int coll_dis);
void				render_image(t_data *game, t_image *img, int x, int y);
void				init_crowbar(t_data *game);
void				init_handgun(t_data *game);
void				get_vector_right(t_data *g, t_point3d *v_right);
void				get_vector_down(t_data *g, t_point3d *v_right,
						t_point3d *v_down);
void				rotate_u(t_point3d *todo, t_point3d u, t_point3d v,
						float angle);
void				change_image_color(t_data *game, t_image *img);
int					handle_animation_state(t_data *game,
						struct s_animation *animation, __uint64_t delay);
int					handle_key_press(int key, t_data *game);
int					handle_key_release(int key, t_data *game);
void				destroy_imgs(t_data *game);
int					close_window(t_data *game);
unsigned int		rgb_to_int(t_color c);
t_color				int_to_rgb(unsigned int color);
void				shade_color(t_color *c, float shading);
t_color				*mix_color(t_color *c1, t_color c2, int base, int blend);
void				set_rgb(unsigned int r, unsigned int g, unsigned int b,
						t_color *c);
void				update_animation(t_data *game);
void				draw_minimap(t_data *game);
void				check_file(t_data *game, char *path, char *ext);
void				init_hud(t_data *game);
void				set_image(t_data *game, t_image **img, char *path);

#endif