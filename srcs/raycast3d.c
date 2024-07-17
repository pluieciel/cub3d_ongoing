#include "cub3d.h"

void	add_door_h(t_raycast *r)
{
	r->num_doors_h++;
	r->doors_h[r->num_doors_h][0] = r->h[0];
	r->doors_h[r->num_doors_h][1] = r->h[1];
	r->doors_h[r->num_doors_h][2] = r->h[2];
	r->doors_h[r->num_doors_h][3] = distance(r->h[0], r->h[1],
			r->g->player.x, r->g->player.y);
	r->doors_h[r->num_doors_h][4] = r->h[4];
	r->doors_h[r->num_doors_h][5] = r->h[5];
	r->doors_h[r->num_doors_h][6] = r->h[6];
}

float	raycast_h_3d2(t_raycast *r)
{
	int	range;

	range = 0;
	while (range < RAYCAST_RANGE && r->h[0] / B_SIZE > 0 && r->h[0]
		/ B_SIZE < r->g->map_w && r->h[2] + r->g->player.z <= B_SIZE / 2
		&& r->h[2] + r->g->player.z >= -B_SIZE / 2)
	{
		r->h[5] = (int)r->h[0] / B_SIZE;
		r->h[6] = (int)r->h[1] / B_SIZE - (r->y < 0);
		if (r->y != 0 && r->h[6] >= 0 && r->h[6] < r->g->map_h)
		{
			if (r->g->map[(int)r->h[6]][(int)r->h[5]] == 1)
				return (distance(r->h[0], r->h[1], r->g->player.x,
						r->g->player.y));
			else if (r->g->map[(int)r->h[6]][(int)r->h[5]] >= 2)
				add_door_h(r);
		}
		range++;
		r->h[0] += r->x / fabs(r->y) * B_SIZE;
		r->h[1] += ((r->y > 0) * 2 - 1) * B_SIZE;
		r->h[2] += r->z / fabs(r->y) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

void	reset_h(t_raycast *r)
{
	r->h[0] = r->g->player.x;
	r->h[1] = r->g->player.y;
	r->h[2] = r->g->player.z;
	r->h[4] = 0;
}

float	raycast_h_3d(t_raycast *r)
{
	if (r->y < 0)
	{
		r->h[1] = r->g->player.y - r->g->player.y % B_SIZE;
		r->h[0] = r->g->player.x - (r->g->player.y % B_SIZE)
			* r->x / r->y;
		r->h[2] = (r->g->player.y % B_SIZE) * r->z / -r->y;
		r->h[4] = 1;
	}
	else if (r->y > 0)
	{
		r->h[1] = r->g->player.y + B_SIZE - r->g->player.y % B_SIZE;
		r->h[0] = r->g->player.x + (B_SIZE - r->g->player.y % B_SIZE)
			* r->x / r->y;
		r->h[2] = (B_SIZE - r->g->player.y % B_SIZE) * r->z
			/ r->y;
		r->h[4] = -1;
	}
	else
	{
		reset_h(r);
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_h_3d2(r));
}

void	raycast_3d(t_raycast *r)
{
	r->num_doors_h = -1;
	r->h[3] = raycast_h_3d(r);
	r->num_doors_v = -1;
	r->v[3] = raycast_v_3d(r);
	if (r->h[3] < r->v[3])
		r->res_rc_3d = r->h;
	else
		r->res_rc_3d = r->v;
}
