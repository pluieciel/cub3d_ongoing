/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <jlefonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:08:08 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/22 09:18:51 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_color	get_wall_color(t_raycast *ray, t_image *img, float pos)
{
	float	col;
	float	row;

	col = round(fmod(pos, B_SIZE) / B_SIZE * img->w);
	row = round((1 - fmod(ray->rc->z + ray->g->player.z + 32, B_SIZE) / B_SIZE)
			* img->h);
	return (int_to_rgb(get_image_color(img, row, col)));
}
