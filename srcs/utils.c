#include "cub3d.h"

void destroy_animation(t_data *game, t_animation *anim)
{
	t_image *img;
	while (anim->frames)
	{
		img = (t_image *)anim->frames->content;
		if (img)
			mlx_destroy_image(game->mlx_ptr, img->ptr);
		anim->frames = anim->frames->next;
		if (anim->frames == anim->head)
			break ;
	}
}

void	destroy_imgs(t_data *game)
{
	t_hud *hud;

	if (game->img.ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_sky.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_no.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_so.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_ea.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_wall_we.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_floor.ptr);
	mlx_destroy_image(game->mlx_ptr, game->img_door.ptr);
	destroy_animation(game, &game->crowbar.draw);
	destroy_animation(game, &game->crowbar.holster);
	destroy_animation(game, &game->crowbar.attack);
	destroy_animation(game, &game->crowbar.attack_hit);
	destroy_animation(game, &game->handgun.draw);
	destroy_animation(game, &game->handgun.holster);
	destroy_animation(game, &game->handgun.shoot);
	while (game->hud_elem)
	{
		hud = (t_hud *)game->hud_elem->content;
		mlx_destroy_image(game->mlx_ptr, hud->img->ptr);
		game->hud_elem = game->hud_elem->next;
	}
}

int	close_window(t_data *game)
{
	destroy_imgs(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	gc_free(game->gc, "", 1);
	exit(EXIT_SUCCESS);
}

void	check_file(t_data *game, char *path, char *ext)
{
	int	fd;

	if (ft_isvalid_extension(path, ext) != 0)
		exit(gc_free(game->gc, "Error: invalid file extension\n", 2));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(gc_free(game->gc, "Error: invalid file\n", 2));
	close(fd);
}

void	set_image(t_data *game, t_image **img, char *path)
{
	*img = gc_malloc(sizeof(t_image), &game->gc);
	(*img)->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &(*img)->w,
			&(*img)->h);
	(*img)->addr = mlx_get_data_addr((*img)->ptr, &(*img)->bpp,
			&(*img)->line_len, &(*img)->endian);
}
