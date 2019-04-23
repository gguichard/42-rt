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
	else if (object->type == RAYOBJ_ELLIPSOID)
		return (get_ellipsoid_intersect_dist(object, origin, direction));
	else if (object->type == RAYOBJ_HOLED_CUBE)
		return (get_holed_cube_intersect_dist(object, origin, direction));
	else
		return (-1);
}

#include <stdio.h>
t_vec3d	get_intersect_normal_2(t_ray_object *object, t_vec3d intersect)
{
	double	tmp1;
	double	tmp2;

	if (object->type == RAYOBJ_TORUS)
	{
		tmp1 = pow(object->big_radius, 2);
		tmp2 = vec3d_length2(intersect) - (pow(object->radius, 2) + tmp1);
		intersect.x = intersect.x * tmp2;
		intersect.y = intersect.y * (tmp2 + 2 * tmp1);
		intersect.z = intersect.z * tmp2;
	}
	else if (object->type == RAYOBJ_TRIANGLE)
	{
		intersect = vec3d_cross(vec3d_sub(object->vertices[1]
					, object->vertices[0]), vec3d_sub(object->vertices[2]
						, object->vertices[0]));
	}
	else if (object->type == RAYOBJ_ELLIPSOID)
	{
		intersect.x = intersect.x / pow(object->size.x, 2);
		intersect.y = intersect.y / pow(object->size.y, 2);
		intersect.z = intersect.z / pow(object->size.z, 2);
	}
	return (intersect);
}

t_vec3d	get_intersect_normal(t_ray_object *object, t_vec3d intersect)
{
	if (object->type == RAYOBJ_PLANE)
		intersect = (t_vec3d){0, 1, 0};
	else if (object->type == RAYOBJ_CYLINDER || object->type == RAYOBJ_CONE)
		intersect.z = .0;
	else
		intersect = get_intersect_normal_2(object, intersect);
	return (vec3d_unit(intersect));
}
