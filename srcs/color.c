#include "cub3d.h"

unsigned int	rgb_to_int(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}

t_color	int_to_rgb(unsigned int color)
{
	t_color	c;

	c.r = (color & 0xFF0000) >> 16;
	c.g = (color & 0xFF00) >> 8;
	c.b = color & 0xFF;
	return (c);
}

void	set_rgb(unsigned int r, unsigned int g, unsigned int b, t_color *c)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void	shade_color(t_color *c, float shading)
{
	c->r = (int)round(c->r * shading);
	c->g = (int)round(c->g * shading);
	c->b = (int)round(c->b * shading);
}

t_color	*mix_color(t_color *c1, t_color c2, int base, int blend)
{
	int	weight;

	weight = base + blend;
	c1->r = (c1->r * base + c2.r * blend) / weight;
	c1->g = (c1->g * base + c2.g * blend) / weight;
	c1->b = (c1->b * base + c2.b * blend) / weight;
	return (c1);
}
