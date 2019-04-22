#include <math.h>
#include "ray_object.h"
#include "vec3d.h"

double	get_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	if (object->type == RAYOBJ_SPHERE)
		return (get_sphere_intersect_dist(object, origin, direction));
	else if (object->type == RAYOBJ_PLANE)
		return (get_plane_intersect_dist(object, origin, direction));
	else if (object->type == RAYOBJ_CYLINDER)
		return (get_cylinder_intersect_dist(object, origin, direction));
	else if (object->type == RAYOBJ_CONE)
		return (get_cone_intersect_dist(object, origin, direction));
	else if (object->type == RAYOBJ_TORUS)
		return (get_torus_intersect_dist(object, origin, direction));
	else if (object->type == RAYOBJ_TRIANGLE)
		return (get_triangle_intersect_dist(object, origin, direction));
	else
		return (-1);
}

t_vec3d	get_intersect_normal(t_ray_object *object, t_vec3d intersect)
{
	double	tmp1;
	double	tmp2;

	if (object->type == RAYOBJ_PLANE)
		intersect = (t_vec3d){0, 1, 0};
	else if (object->type == RAYOBJ_CYLINDER || object->type == RAYOBJ_CONE)
		intersect.z = .0;
	else if (object->type == RAYOBJ_TORUS)
	{
		tmp1 = pow(object->big_radius, 2);
		tmp2 = vec3d_length2(intersect) - (pow(object->radius, 2) + tmp1);
		intersect.x = 4 * intersect.x * tmp2;
		intersect.y = 4 * intersect.y * (tmp2 + 2 * tmp1);
		intersect.z = 4 * intersect.z * tmp2;
	}
	else if (object->type == RAYOBJ_TRIANGLE)
	{
		intersect = vec3d_cross(vec3d_sub(object->vertices[1]
					, object->vertices[0]), vec3d_sub(object->vertices[2]
						, object->vertices[0]));
	}
	return (vec3d_unit(intersect));
}
