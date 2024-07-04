#include "../includes/cub3D.h"

static void	ft_put_pixel(t_img1 *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void	ft_bresenham_low(t_point *a, t_point *b, t_delta delta,
		t_img1 *img)
{
	int		p;

	p = 2 * delta.dy - delta.dx;
	while (a->x != b->x)
	{
		ft_put_pixel(img, a->x, a->y, a->color);
		if (a->x < b->x)
			a->x += 1;
		else
			a->x -= 1;
		if (p < 0)
			p += 2 * delta.dy;
		else
		{
			p += 2 * delta.dy - 2 * delta.dx;
			if (a->y < b->y)
				a->y += 1;
			else
				a->y -= 1;
		}
	}
}

static void	ft_bresenham_high(t_point *a, t_point *b, t_delta delta,
		t_img1 *img)
{
	int		p;

	p = 2 * delta.dx - delta.dy;
	while (a->y != b->y)
	{
		ft_put_pixel(img, a->x, a->y, a->color);
		if (a->y < b->y)
			a->y += 1;
		else
			a->y -= 1;
		if (p < 0)
			p += 2 * delta.dx;
		else
		{
			p += 2 * delta.dx - 2 * delta.dy;
			if (a->x < b->x)
				a->x += 1;
			else
				a->x -= 1;
		}
	}
}

void	ft_bresenham(t_point a, t_point b, t_img1 *img)
{
	t_delta	delta;

	delta.dx = abs(b.x - a.x);
	delta.dy = abs(b.y - a.y);
	if (delta.dx > delta.dy)
		ft_bresenham_low(&a, &b, delta, img);
	else
		ft_bresenham_high(&a, &b, delta, img);
}
