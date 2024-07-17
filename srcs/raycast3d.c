#include "cub3d.h"

void	add_door_h(t_raycast *r)
{
	r->num_doors_h++;
	r->doors_h[r->num_doors_h][0] = r->res_rc_h.x;
	r->doors_h[r->num_doors_h][1] = r->res_rc_h.y;
	r->doors_h[r->num_doors_h][2] = r->res_rc_h.z;
	r->doors_h[r->num_doors_h][3] = distance(r->res_rc_h.x, r->res_rc_h.y,
			r->g->player.x, r->g->player.y);
	r->doors_h[r->num_doors_h][4] = r->res_rc_h.dir;
	r->doors_h[r->num_doors_h][5] = r->res_rc_h.map_x;
	r->doors_h[r->num_doors_h][6] = r->res_rc_h.map_y;
}

float	raycast_h_3d2(t_raycast *r)
{
	int	range;

	range = 0;
	while (range < RAYCAST_RANGE && r->res_rc_h.x / B_SIZE > 0 && r->res_rc_h.x
		/ B_SIZE < r->g->map_w && r->res_rc_h.z + r->g->player.z <= B_SIZE / 2
		&& r->res_rc_h.z + r->g->player.z >= -B_SIZE / 2)
	{
		r->res_rc_h.map_x = (int)r->res_rc_h.x / B_SIZE;
		r->res_rc_h.map_y = (int)r->res_rc_h.y / B_SIZE - (r->p.y < 0);
		if (r->p.y != 0 && r->res_rc_h.map_y >= 0 && r->res_rc_h.map_y < r->g->map_h)
		{
			if (r->g->map[(int)r->res_rc_h.map_y][(int)r->res_rc_h.map_x] == 1)
				return (distance(r->res_rc_h.x, r->res_rc_h.y, r->g->player.x,
						r->g->player.y));
			else if (r->g->map[(int)r->res_rc_h.map_y][(int)r->res_rc_h.map_x] >= 2)
				add_door_h(r);
		}
		range++;
		r->res_rc_h.x += r->p.x / fabs(r->p.y) * B_SIZE;
		r->res_rc_h.y += ((r->p.y > 0) * 2 - 1) * B_SIZE;
		r->res_rc_h.z += r->p.z / fabs(r->p.y) * B_SIZE;
	}
	return ((RAYCAST_RANGE + 1.0) * B_SIZE);
}

void	reset_h(t_raycast *r)
{
	r->res_rc_h.x = r->g->player.x;
	r->res_rc_h.y = r->g->player.y;
	r->res_rc_h.z = r->g->player.z;
	r->res_rc_h.dir = 0;
}

float	raycast_h_3d(t_raycast *r)
{
	if (r->p.y < 0)
	{
		r->res_rc_h.y = r->g->player.y - r->g->player.y % B_SIZE;
		r->res_rc_h.x = r->g->player.x - (r->g->player.y % B_SIZE)
			* r->p.x / r->p.y;
		r->res_rc_h.z = (r->g->player.y % B_SIZE) * r->p.z / -r->p.y;
		r->res_rc_h.dir = 1;
	}
	else if (r->p.y > 0)
	{
		r->res_rc_h.y = r->g->player.y + B_SIZE - r->g->player.y % B_SIZE;
		r->res_rc_h.x = r->g->player.x + (B_SIZE - r->g->player.y % B_SIZE)
			* r->p.x / r->p.y;
		r->res_rc_h.z = (B_SIZE - r->g->player.y % B_SIZE) * r->p.z
			/ r->p.y;
		r->res_rc_h.dir = -1;
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
	r->res_rc_h.dis = raycast_h_3d(r);
	r->num_doors_v = -1;
	r->res_rc_v.dis = raycast_v_3d(r);
	if (r->res_rc_h.dis < r->res_rc_v.dis)
		r->res_rc = &r->res_rc_h;
	else
		r->res_rc = &r->res_rc_v;
}
