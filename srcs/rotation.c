#include "cub3d.h"

t_point3d   *ro_on_z_to_xz(t_point3d p)
{
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float a = p.angle;
    t_point3d *newp = (t_point3d *)malloc(sizeof(t_point3d));
    newp->x = cos(a) * x + sin(a) * y;
    newp->y = -sin(a) * x + cos(a) * y;
    newp->z = z;
    newp->angle = a;
    return newp;
}

t_point3d	*ro_on_y(t_point3d p, float angle_z)
{
    float x = p.x;
    float y = p.y;
    float z = p.z;
    t_point3d *newp = (t_point3d *)malloc(sizeof(t_point3d));
    newp->x = x * cos(angle_z) - z * sin(angle_z);
    newp->y = y;
    newp->z = x * sin(angle_z) + z * cos(angle_z);
    newp->angle = p.angle;
    return newp;
}

t_point3d	*ro_back_on_z(t_point3d p)
{
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float a = p.angle;
    t_point3d *newp = (t_point3d *)malloc(sizeof(t_point3d));
    newp->x = cos(a) * x - sin(a) * y;
    newp->y = sin(a) * x + cos(a) * y;
    newp->z = z;
    newp->angle = a;
    return newp;
}

t_point3d	*cross(t_point3d p1, t_point3d p2)
{
    t_point3d *newp = (t_point3d *)malloc(sizeof(t_point3d));
    newp->x = p1.y * p2.z - p1.z * p2.y;
    newp->y = p1.z * p2.x - p1.x * p2.z;
    newp->z = p1.x * p2.y - p1.y * p2.x;
    newp->angle = 0;
    return newp;
}