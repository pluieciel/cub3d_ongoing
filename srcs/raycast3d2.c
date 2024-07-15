#include "cub3d.h"

void	add_door_v(t_raycast *r)
{
	r->num_doors_v++;
	r->doors_v[r->num_doors_v][0] = r->v[0];
	r->doors_v[r->num_doors_v][1] = r->v[1];
	r->doors_v[r->num_doors_v][2] = r->v[2];
	r->doors_v[r->num_doors_v][3] = distance(r->v[0], r->v[1],
			r->g->player.pos[0], r->g->player.pos[1]);
	r->doors_v[r->num_doors_v][4] = r->v[4];
	r->doors_v[r->num_doors_v][5] = r->v[5];
	r->doors_v[r->num_doors_v][6] = r->v[6];
}

float	raycast_v_3d2(t_raycast *r)
{
	int		range;

	range = 0;
	while (range < RAYCAST_RANGE
		&& r->v[1] / B_SIZE > 0 && r->v[1] / B_SIZE < r->g->map_h
		&& r->v[2] + r->g->player.z <= B_SIZE / 2 && r->v[2] + r->g->player.z >= -B_SIZE / 2)
	{
		r->v[5] = (int)r->v[0] / B_SIZE - (r->xyz[0] < 0);
		r->v[6] = (int)r->v[1] / B_SIZE;
		if (r->xyz[0] != 0 && r->v[5] >= 0 && r->v[5] < r->g->map_w)
		{
			if (r->g->map[(int)r->v[6]][(int)r->v[5]] == 1)
				return (distance(r->v[0], r->v[1],
						r->g->player.pos[0], r->g->player.pos[1]));
			else if (r->g->map[(int)r->v[6]][(int)r->v[5]] >= 2)
				add_door_v(r);
		}
		range++;
		r->v[1] += r->xyz[1] / fabs(r->xyz[0]) * B_SIZE;
		r->v[0] += ((r->xyz[0] > 0) * 2 - 1) * B_SIZE;
		r->v[2] += r->xyz[2] / fabs(r->xyz[0]) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

float	raycast_v_3d(t_raycast *r)
{
	if (r->xyz[0] < 0)
	{
		r->v[0] = r->g->player.pos[0] - r->g->player.pos[0] % B_SIZE;
		r->v[1] = r->g->player.pos[1] - (r->g->player.pos[0] % B_SIZE)
			* r->xyz[1] / r->xyz[0];
		r->v[2] = (r->g->player.pos[0] % B_SIZE) * r->xyz[2] / -r->xyz[0];
		r->v[4] = -1;
	}
	else if (r->xyz[0] > 0)
	{
		r->v[0] = r->g->player.pos[0] + B_SIZE - r->g->player.pos[0] % B_SIZE;
		r->v[1] = r->g->player.pos[1] + (B_SIZE - r->g->player.pos[0] % B_SIZE)
			* r->xyz[1] / r->xyz[0];
		r->v[2] = (B_SIZE - r->g->player.pos[0] % B_SIZE)
			* r->xyz[2] / r->xyz[0];
		r->v[4] = 1;
	}
	else
	{
		r->v[0] = r->g->player.pos[0];
		r->v[1] = r->g->player.pos[1];
		r->h[2] = r->g->player.z;
		r->v[4] = 0;
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_v_3d2(r));
}
