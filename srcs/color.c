#include "cub3d.h"

unsigned int	to_rgb(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}

void	from_rgb(unsigned int color, t_color *c)
{
	c->r = (color & 0xFF0000) >> 16;
	c->g = (color & 0xFF00) >> 8;
	c->b = color & 0xFF;
}

void	from_r_g_b(int r, int g, int b, t_color *c)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void	add_shadow(t_color *c, float shadow)
{
	c->r = (int)round(c->r * shadow);
	c->g = (int)round(c->g * shadow);
	c->b = (int)round(c->b * shadow);
}

void	mix_color(t_color *c1, t_color c2, int a, int b)
{
	int tot;

	tot = a + b;
	c1->r = (c1->r * a + c2.r * b) / tot;
	c1->g = (c1->g * a + c2.g * b) / tot;
	c1->b = (c1->b * a + c2.b * b) / tot;
}