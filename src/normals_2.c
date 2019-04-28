#include "ray_object.h"
#include "vec3d.h"
#include <math.h>

t_vec3d	get_triangle_normal(t_ray_object *object, t_vec3d intersect)
{
	t_vec3d	tmp1;
	t_vec3d	tmp2;

	tmp1 = vec3d_sub(object->vertices[1], object->vertices[0]);
	tmp2 = vec3d_sub(object->vertices[2], object->vertices[0]);
	intersect = vec3d_cross(tmp1, tmp2);
	return (vec3d_unit(intersect));
}

t_vec3d	get_ellipsoid_normal(t_ray_object *object, t_vec3d intersect)
{
	intersect.x /= (object->size.x * object->size.x);
	intersect.y /= (object->size.y * object->size.y);
	intersect.z /= (object->size.z * object->size.z);
	return (vec3d_unit(intersect));
}

t_vec3d	get_hyperboloid_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	intersect.z = .0;
	return (vec3d_unit(intersect));
}

t_vec3d	get_holed_cube_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	intersect.x = 4 * pow(intersect.x, 3) - 10.0 * intersect.x;
	intersect.y = 4 * pow(intersect.y, 3) -	10.0 * intersect.y;
	intersect.z = 4 * pow(intersect.z, 3) - 10.0 * intersect.z;
	return (vec3d_unit(intersect));
}
