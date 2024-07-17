#include "cub3d.h"

void	add_door_v(t_raycast *r)
{
	r->num_doors_v++;
	r->doors_v[r->num_doors_v][0] = r->rc_v.x;
	r->doors_v[r->num_doors_v][1] = r->rc_v.y;
	r->doors_v[r->num_doors_v][2] = r->rc_v.z;
	r->doors_v[r->num_doors_v][3] = distance(r->rc_v.x, r->rc_v.y,
			r->g->player.x, r->g->player.y);
	r->doors_v[r->num_doors_v][4] = r->rc_v.dir;
	r->doors_v[r->num_doors_v][5] = r->rc_v.map_x;
	r->doors_v[r->num_doors_v][6] = r->rc_v.map_y;
}

float	raycast_v_3d2(t_raycast *r)
{
	int	range;

	range = 0;
	while (range < RAYCAST_RANGE && r->rc_v.y / B_SIZE > 0 && r->rc_v.y
		/ B_SIZE < r->g->map_h && r->rc_v.z + r->g->player.z <= B_SIZE / 2
		&& r->rc_v.z + r->g->player.z >= -B_SIZE / 2)
	{
		r->rc_v.map_x = (int)r->rc_v.x / B_SIZE - (r->p.x < 0);
		r->rc_v.map_y = (int)r->rc_v.y / B_SIZE;
		if (r->p.x != 0 && r->rc_v.map_x >= 0 && r->rc_v.map_x < r->g->map_w)
		{
			if (r->g->map[(int)r->rc_v.map_y][(int)r->rc_v.map_x] == 1)
				return (distance(r->rc_v.x, r->rc_v.y, r->g->player.x,
						r->g->player.y));
			else if (r->g->map[(int)r->rc_v.map_y][(int)r->rc_v.map_x] >= 2)
				add_door_v(r);
		}
		range++;
		r->rc_v.y += r->p.y / fabs(r->p.x) * B_SIZE;
		r->rc_v.x += ((r->p.x > 0) * 2 - 1) * B_SIZE;
		r->rc_v.z += r->p.z / fabs(r->p.x) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

void	reset_v(t_raycast *r)
{
	r->rc_v.x = r->g->player.x;
	r->rc_v.y = r->g->player.y;
	r->rc_v.z = r->g->player.z;
	r->rc_v.dir = 0;
}

float	raycast_v_3d(t_raycast *r)
{
	if (r->p.x < 0)
	{
		r->rc_v.x = r->g->player.x - r->g->player.x % B_SIZE;
		r->rc_v.y = r->g->player.y - (r->g->player.x % B_SIZE)
			* r->p.y / r->p.x;
		r->rc_v.z = (r->g->player.x % B_SIZE) * r->p.z / -r->p.x;
		r->rc_v.dir = -1;
	}
	else if (r->p.x > 0)
	{
		r->rc_v.x = r->g->player.x + B_SIZE - r->g->player.x % B_SIZE;
		r->rc_v.y = r->g->player.y + (B_SIZE - r->g->player.x % B_SIZE)
			* r->p.y / r->p.x;
		r->rc_v.z = (B_SIZE - r->g->player.x % B_SIZE) * r->p.z
			/ r->p.x;
		r->rc_v.dir = 1;
	}
	else
	{
		reset_v(r);
		return ((RAYCAST_RANGE + 1.0) * B_SIZE);
	}
	return (raycast_v_3d2(r));
}
