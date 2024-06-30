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

int main()
{
    point p = {1, 1, 1, M_PI / 4};
    point *newp;
    newp = &p;
    printf("x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    newp = ro_on_z_to_xz(p);
    printf("x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    newp = ro_on_y(*newp, -asin(1 / sqrt(3)));
    printf("x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    newp = ro_back_on_z(*newp);
    printf("x: %f, y: %f, z: %f\n", newp->x, newp->y, newp->z); fflush(stdout);
    
    return 0;
}