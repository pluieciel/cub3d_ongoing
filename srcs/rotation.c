#include "cub3d.h"

void	get_vector_right(t_data *g, t_point3d *v_right)
{
	v_right->x = -g->player.dir[1];
	v_right->y = g->player.dir[0];
	v_right->z = 0;
}

void	get_vector_down(t_data *g, t_point3d *v_right, t_point3d *v_down)
{
	v_down->x = v_right->y * g->player.dir3d.z - v_right->z * g->player.dir3d.y;
	v_down->y = v_right->z * g->player.dir3d.x - v_right->x * g->player.dir3d.z;
	v_down->z = v_right->x * g->player.dir3d.y - v_right->y * g->player.dir3d.x;
}

float	dot(t_point3d u, t_point3d v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

void	rotate_u(t_point3d *todo, t_point3d u, t_point3d v, float angle)
{
	double		k[4];
	double		len;
	t_point3d	old;

	old.x = todo->x;
	old.y = todo->y;
	old.z = todo->z;
	k[0] = dot(old, u);
	k[1] = dot(old, v);
	k[2] = k[0] * cos(angle) - k[1] * sin(angle);
	k[3] = k[0] * sin(angle) + k[1] * cos(angle);
	todo->x = k[2] * u.x + k[3] * v.x;
	todo->y = k[2] * u.y + k[3] * v.y;
	todo->z = k[2] * u.z + k[3] * v.z;
	len = sqrt(todo->x * todo->x + todo->y * todo->y + todo->z * todo->z);
	todo->x /= len;
	todo->y /= len;
	todo->z /= len;
}

void	printv(t_point3d p)
{
	printf("x: %f, y: %f, z: %f, len: %f\n", p.x, p.y, p.z, sqrt(p.x * p.x + p.y
			* p.y + p.z * p.z));
}
