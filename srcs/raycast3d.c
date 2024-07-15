#include "cub3d.h"

void	add_door_h(t_raycast *r)
{
	r->num_doors_h++;
	r->doors_h[r->num_doors_h][0] = r->h[0];
	r->doors_h[r->num_doors_h][1] = r->h[1];
	r->doors_h[r->num_doors_h][2] = r->h[2];
	r->doors_h[r->num_doors_h][3] = distance(r->h[0], r->h[1],
			r->g->player.pos[0], r->g->player.pos[1]);
	r->doors_h[r->num_doors_h][4] = r->h[4];
	r->doors_h[r->num_doors_h][5] = r->h[5];
	r->doors_h[r->num_doors_h][6] = r->h[6];
}

float	raycast_h_3d2(t_raycast *r)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE
		&& r->h[0] / B_SIZE > 0 && r->h[0] / B_SIZE < r->g->map_w
		&& r->h[2] + r->g->player.pos[2] <= B_SIZE / 2 && r->h[2] + r->g->player.pos[2] >= -B_SIZE / 2)
	{
		r->h[5] = (int)r->h[0] / B_SIZE;
		r->h[6] = (int)r->h[1] / B_SIZE - (r->xyz[1] < 0);
		if (r->xyz[1] != 0 && r->h[6] >= 0 && r->h[6] < r->g->map_h)
		{
			if (r->g->map[(int)r->h[6]][(int)r->h[5]] == 1)
				return (distance(r->h[0], r->h[1],
						r->g->player.pos[0], r->g->player.pos[1]));
			else if (r->g->map[(int)r->h[6]][(int)r->h[5]] >= 2)
				add_door_h(r);
		}
		range++;
		r->h[0] += r->xyz[0] / fabs(r->xyz[1]) * B_SIZE;
		r->h[1] += ((r->xyz[1] > 0) * 2 - 1) * B_SIZE;
		r->h[2] += r->xyz[2] / fabs(r->xyz[1]) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_h_3d(t_raycast *r)
{
	if (r->xyz[1] < 0)
	{
		r->h[1] = r->g->player.pos[1] - r->g->player.pos[1] % B_SIZE;
		r->h[0] = r->g->player.pos[0] - (r->g->player.pos[1] % B_SIZE)
			* r->xyz[0] / r->xyz[1];
		r->h[2] = (r->g->player.pos[1] % B_SIZE) * r->xyz[2] / -r->xyz[1];
		r->h[4] = 1;
	}
	else if (r->xyz[1] > 0)
	{
		r->h[1] = r->g->player.pos[1] + B_SIZE - r->g->player.pos[1] % B_SIZE;
		r->h[0] = r->g->player.pos[0] + (B_SIZE - r->g->player.pos[1] % B_SIZE)
			* r->xyz[0] / r->xyz[1];
		r->h[2] = (B_SIZE - r->g->player.pos[1] % B_SIZE)
			* r->xyz[2] / r->xyz[1];
		r->h[4] = -1;
	}
	else
	{
		r->h[0] = r->g->player.pos[0];
		r->h[1] = r->g->player.pos[1];
		r->h[4] = 0;
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