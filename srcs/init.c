#include "cub3D.h"

void	init(t_data *game)
{
	game->gc = NULL;
	game->win_ptr = NULL;
	game->mlx_ptr = NULL;
	game->player.pos[0] = 0;
	game->player.pos[1] = 0;
	game->player.dir[0] = 0;
	game->player.dir[1] = 0;
	game->player.dir3D.x = 0;
	game->player.dir3D.y = 0;
	game->player.dir3D.z = 0;
	game->player.dir3D.angle = 0;
	game->key.w = 0;
	game->key.a = 0;
	game->key.s = 0;
	game->key.d = 0;
	game->key.left = 0;
	game->key.right = 0;
	game->key.up = 0;
	game->key.down = 0;
	game->key.one = 0;
	game->key.two = 0;
	game->elem_n = 0;
	game->map_index = -1;
	game->map_h = 0;
	game->map_w = 0;
	game->dis_p_s = DIS_P_S;
	game->time = get_timestamp_ms();
	game->op_door = 0;
	game->doors = NULL;
	game->mlx_ptr = mlx_init();
	game->gc = (t_gc *)gc_insert(game->gc, game->mlx_ptr);
	game->img.w = WIN_W;
	game->img.h = WIN_H;
	game->img.ptr = mlx_new_image(game->mlx_ptr,
			game->img.w, game->img.h);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_len, &game->img.endian);
	game->img_wall_no.w = 0;
	game->img_wall_no.h = 0;
	game->img_wall_no.ptr = NULL;
	game->img_wall_no.addr = NULL;
	game->img_wall_so.w = 0;
	game->img_wall_so.h = 0;
	game->img_wall_so.ptr = NULL;
	game->img_wall_so.addr = NULL;
	game->img_wall_ea.w = 0;
	game->img_wall_ea.h = 0;
	game->img_wall_ea.ptr = NULL;
	game->img_wall_ea.addr = NULL;
	game->img_wall_we.w = 0;
	game->img_wall_we.h = 0;
	game->img_wall_we.ptr = NULL;
	game->img_wall_we.addr = NULL;
	game->img_sky.w = 0;
	game->img_sky.h = 0;
	game->img_sky.ptr = NULL;
	game->img_sky.addr = NULL;
	game->img_floor.w = 0;
	game->img_floor.h = 0;
	game->img_floor.ptr = NULL;
	game->img_floor.addr = NULL;
	game->img_door.w = 0;
	game->img_door.h = 0;
	game->img_door.ptr = NULL;
	game->img_door.addr = NULL;
	game->img_hud_health.w = 0;
	game->img_hud_health.h = 0;
	game->img_hud_health.ptr = NULL;
	game->img_hud_health.addr = NULL;
	game->animation_time = 0;
	game->left_click = 0;
}

void init_animation(t_data *game, struct s_animation *animation, char *state, int frames)
{
	int i;
	int fd;
	t_image *img;
	char path[48];

	i = 1;
	while (i <= frames)
	{
	    img = gc_malloc(sizeof(t_image), &game->gc);
	    snprintf(path, sizeof(path), "textures/%s%d.xpm", state, i);
		fd = open(path, O_RDONLY);
		if (fd < 0)
			exit(gc_free(game->gc, "Error: invalid file\n", 2));
		close(fd);
	    img->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &img->w, &img->h);
	    img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, &img->endian);
	    ft_lstadd_back(&animation->frames, ft_lstnew_gc(img, &game->gc));
	    i++;
	}
	ft_lstlast(animation->frames)->next = animation->frames;
	animation->head = animation->frames;
}

void init_crowbar(t_data *game)
{
	game->crowbar.draw.frames = NULL;
	game->crowbar.draw.head = NULL;
	game->crowbar.attack.frames = NULL;
	game->crowbar.attack.head = NULL;
	game->crowbar.attack_hit.frames = NULL;
	game->crowbar.attack_hit.head = NULL;
	game->crowbar.holster.frames = NULL;
	game->crowbar.holster.head = NULL;
	game->crowbar.state = CROWBAR_DRAW;
	game->crowbar.equiped = 0;
	init_animation(game, &game->crowbar.draw, "crowbar/draw", 12);
	init_animation(game, &game->crowbar.attack, "crowbar/attack", 13);
	init_animation(game, &game->crowbar.attack_hit, "crowbar/attack_hit", 13);
	init_animation(game, &game->crowbar.holster, "crowbar/holster", 12);
}

void init_handgun(t_data *game)
{
	game->handgun.draw.frames = NULL;
	game->handgun.draw.head = NULL;
	game->handgun.shoot.frames = NULL;
	game->handgun.shoot.head = NULL;
	game->handgun.holster.frames = NULL;
	game->handgun.holster.head = NULL;
	game->handgun.state = HANDGUN_IDLE;
	game->handgun.equiped = 0;
	init_animation(game, &game->handgun.draw, "handgun/draw", 15);
	init_animation(game, &game->handgun.shoot, "handgun/shoot", 14);
	init_animation(game, &game->handgun.holster, "handgun/holster", 15);
}
