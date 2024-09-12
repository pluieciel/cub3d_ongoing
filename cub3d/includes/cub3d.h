/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <jlefonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:10:20 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/22 09:13:53 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft_gc/includes/libft_gc.h"
# include "../../minilibx/mlx.h"
# include "../../minilibx/mlx_int.h"
# include <X11/X.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define WIN_W 1280
# define WIN_H 720
# define FPS 60
# define B_SIZE 64
# define ROT_SPEED 0.1
# define DIS_P_S 640
# define RAYCAST_RANGE 20
# define ELEM_N 6
# define SPEED 4
# define M_PI 3.14159265358979323846
# define TRANSPARENT_COLOR 0xFF000000

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;

typedef struct s_point3d
{
	float			x;
	float			y;
	float			z;
}					t_point3d;

typedef struct s_player
{
	int				x;
	int				y;
	float			z;
	float			dir_x;
	float			dir_y;
	t_point3d		v_right;
	t_point3d		v_down;
	t_point3d		dir3d;
}					t_player;

typedef struct s_key
{
	bool			w;
	bool			a;
	bool			s;
	bool			d;
	bool			left;
	bool			right;
	bool			up;
	bool			down;
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

typedef struct s_res_rc
{
	float			x;
	float			y;
	float			z;
	float			map_x;
	float			map_y;
	float			dis;
	float			dir;
}					t_res_rc;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			**visited;
	float			**map;
	int				map_w;
	int				map_h;
	int				map_index;
	int				elem_n;
	int				dis_p_s;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	t_player		player;
	t_key			key;
	t_gc			*gc;
	t_image			img;
	t_image			img_wall_no;
	t_image			img_wall_so;
	t_image			img_wall_ea;
	t_image			img_wall_we;
	t_res_rc		rc_h;
	t_res_rc		rc_v;
	t_res_rc		*rc;
	__uint64_t		time;
	__uint64_t		timestep;
}					t_data;

typedef struct s_raycast
{
	float			nearest_wall_dis;
	int				col_start;
	int				col_end;
	t_data			*g;
	t_point3d		p;
	t_point3d		*v_down;
	t_point3d		*v_right;
	t_res_rc		rc_h;
	t_res_rc		rc_v;
	t_res_rc		*rc;
}					t_raycast;

float				distance(float x1, float y1, float x2, float y2);
float				raycast_3d_h(t_raycast *r);
float				raycast_3d_v(t_raycast *r);
int					close_window(t_data *game);
int					handle_key_press(int key, t_data *game);
int					handle_key_release(int key, t_data *game);
int					isvalid_map(t_data *game);
int					main(int ac, char *av[]);
int					render(t_data *game);
t_color				get_wall_color(t_raycast *ray, t_image *img, float pos);
t_color				int_to_rgb(unsigned int color);
t_color				*mix_color(t_color *c1, t_color c2, int base, int blend);
__uint64_t			get_timestamp_ms(void);
unsigned int		get_image_color(t_image *img, int row, int col);
unsigned int		rgb_to_int(t_color c);
void				check_file(t_data *game, char *path, char *ext);
void				destroy_images(t_data *game);
void				draw_pixel(t_raycast *ray, int col, int row);
void				draw_textures(t_data *g);
void				exit_on_error(t_data *game, char *error_msg);
void				get_vector_down(t_data *g, t_point3d *v_right,
						t_point3d *v_down);
void				get_vector_right(t_data *g, t_point3d *v_right);
void				handle_special_keys(int key, t_data *game);
void				hook(t_data *game);
void				init(t_data *game);
void				move_player(t_data *game, float dir_x, float dir_y);
void				parse_elements(t_data *game, char *filename);
void				parse_map(t_data *game, char *filename);
void				raycast_3d(t_raycast *ray);
void				reset_ray(t_raycast *ray, t_res_rc *rc);
void				rotate_player(t_data *game, float dir_x, float dir_y,
						t_point3d *dir3d);
void				rotate_u(t_point3d *todo, t_point3d u, t_point3d v,
						float angle);
void				set_dir(t_data *game, char dir);
void				set_image_color(t_image *img, int row, int col,
						unsigned int color);
void				set_image(t_data *game, t_image *img, char *path);
void				set_rgb(unsigned int r, unsigned int g, unsigned int b,
						t_color *c);
void				shade_color(t_color *c, float shading);
void				update_player(t_data *game);

#endif