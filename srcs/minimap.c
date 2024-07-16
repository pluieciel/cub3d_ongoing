#include "../includes/cub3d.h"

void	draw_block(t_data *game)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		newi;
	int		newj;
	t_color	c;
	t_color	hud_c;
	t_color	c2;

	hud_c = int_to_rgb(game->hud_color);
	i = MM_POS_Y - MM_RADIUS - 1;
	while (++i <= MM_POS_Y + MM_RADIUS)
	{
		j = MM_POS_X - MM_RADIUS - 1;
		while (++j <= MM_POS_X + MM_RADIUS)
		{
			x = ((j - MM_POS_X) * B_SIZE / MM_FACTOR + game->player.x)
				/ B_SIZE;
			y = ((i - MM_POS_Y) * B_SIZE / MM_FACTOR + game->player.y)
				/ B_SIZE;
			if (x >= 0 && y >= 0 && x < game->map_w && y < game->map_h
				&& game->map[y][x] >= 1)
			if (distance(i, j, MM_POS_Y, MM_POS_X) < MM_RADIUS)
			{
				newj = round(-(j - MM_POS_X) * game->player.dir_y
						+ (i - MM_POS_Y) * game->player.dir_x)
					+ MM_POS_X;
				newi = round((j - MM_POS_X) * -game->player.dir_x
						- (i - MM_POS_Y) * game->player.dir_y)
					+ MM_POS_Y;
				c = int_to_rgb(((unsigned int *)game->img.addr)[newi * WIN_W
					+ newj]);
				if (game->map[y][x] == 1)
				{
					mix_color(&c, hud_c, 2, 1);
					shade_color(&c, 0.6);
					((unsigned int *)game->img.addr)[newi * WIN_W
						+ newj] = rgb_to_int(c);
				}
				else if (game->map[y][x] == 3)
				{
					set_rgb(0, 0x80, 0, &c2);
					mix_color(&c, c2, 1, 1);
					((unsigned int *)game->img.addr)[newi * WIN_W
						+ newj] = rgb_to_int(c);
				}
				else if (game->map[y][x] >= 2)
				{
					set_rgb(0x80, 0, 0, &c2);
					mix_color(&c, c2, 1, 1);
					((unsigned int *)game->img.addr)[newi * WIN_W
						+ newj] = rgb_to_int(c);
				}
			}
		}
	}
}

void	draw_bg(t_data *game, int i, int j, float angle)
{
	t_color	c;
	t_color	hud_c;

	hud_c = int_to_rgb(game->hud_color);
	if (distance(i, j, MM_POS_X, MM_POS_Y) < MM_RADIUS)
	{
		c = int_to_rgb(((unsigned int *)game->img.addr)[j * WIN_W + i]);
		if (MM_POS_Y > j && atan(1.0 * abs(i - MM_POS_X) / (MM_POS_Y
					- j)) < angle)
			((unsigned int *)game->img.addr)[j * WIN_W
				+ i] = rgb_to_int(*mix_color(&c, hud_c, 1, 1));
		else
			((unsigned int *)game->img.addr)[j * WIN_W
				+ i] = rgb_to_int(*mix_color(&c, hud_c, 2, 1));
	}
}

void	draw_minimap(t_data *game)
{
	int		i;
	int		j;
	float	angle;

	angle = atan(1.0 * (WIN_W / 2) / game->dis_p_s);
	i = MM_POS_X - MM_RADIUS - 1;
	while (++i <= MM_POS_X + MM_RADIUS)
	{
		j = MM_POS_Y - MM_RADIUS - 1;
		while (++j <= MM_POS_Y + MM_RADIUS)
			draw_bg(game, i, j, angle);
	}
	draw_block(game);
}