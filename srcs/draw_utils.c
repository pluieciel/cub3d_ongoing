#include "cub3d.h"

t_color	get_wall_color(t_raycast *ray, t_image *img, float pos)
{
	float	col;
	float	row;

	col = round(fmod(pos, B_SIZE) / B_SIZE * img->w);
	row = round((1 - fmod(ray->rc->z + ray->g->player.z + 32, B_SIZE) / B_SIZE) * img->h);
	return (int_to_rgb(get_image_color(img, row, col)));
}
