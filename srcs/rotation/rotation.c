#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

typedef struct p
{
    float x;
    float y;
    float z;
    float angle;
} point;

point *ro_on_z_to_xz(point p)
{
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float a = p.angle;
    point *newp = (point *)malloc(sizeof(point));
    newp->x = cos(a) * x + sin(a) * y;
    newp->y = -sin(a) * x + cos(a) * y;
    newp->z = z;
    newp->angle = a;
    return newp;
}

point *ro_on_y(point p, float angle_z)
{
    float x = p.x;
    float y = p.y;
    float z = p.z;
    point *newp = (point *)malloc(sizeof(point));
    newp->x = x * cos(angle_z) - z * sin(angle_z);
    newp->y = y;
    newp->z = x * sin(angle_z) + z * cos(angle_z);
    newp->angle = p.angle;
    return newp;
}

point *ro_back_on_z(point p)
{
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float a = p.angle;
    point *newp = (point *)malloc(sizeof(point));
    newp->x = cos(a) * x - sin(a) * y;
    newp->y = sin(a) * x + cos(a) * y;
    newp->z = z;
    newp->angle = a;
    return newp;
}

point *cross(point p1, point p2)
{
    point *newp = (point *)malloc(sizeof(point));
    newp->x = p1.y * p2.z - p1.z * p2.y;
    newp->y = p1.z * p2.x - p1.x * p2.z;
    newp->z = p1.x * p2.y - p1.y * p2.x;
    newp->angle = 0;
    return newp;
}

int main()
{
    point p = {0, 1, 0, M_PI / 2};
    point *newp;
    newp = &p;
    printf("1, x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    newp = ro_on_z_to_xz(*newp);
    //printf("x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    newp = ro_on_y(*newp, -M_PI / 2);
    //printf("x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    newp = ro_back_on_z(*newp);
    printf("2, x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    newp = cross(*newp, p);
    printf("3, x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    
    return 0;
}