#include <math.h>
#include "ray_object.h"
#include "solver.h"
#include "libft.h"
#include "vec3d.h"

static double	get_plane_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	double	denom;
	t_vec3d	v;
	double	distance;

	denom = vec3d_dot(object->normal, direction);
	if (fabs(denom) > 1e-6)
	{
		v = vec3d_scalar(origin, -1);
		distance = vec3d_dot(v, object->normal) / denom;
		if (distance >= .0)
			return (distance);
	}
	return (-1);
}

static double	get_sphere_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	double	a;
	double	b;
	double	c;

	a = vec3d_length2(direction);
	b = 2 * vec3d_dot(origin, direction);
	c = vec3d_length2(origin) - pow(object->radius, 2);
	return (solve_quadratic_equation(a, b, c));
}

static double	get_cylinder_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	double	a;
	double	b;
	double	c;

	a = pow(direction.x, 2) + pow(direction.y, 2);
	b = 2 * (direction.x * origin.x + direction.y * origin.y);
	c = pow(origin.x, 2) + pow(origin.y, 2) - pow(object->radius, 2);
	return (solve_quadratic_equation(a, b, c));
}

double			get_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	if (object->type == RAYOBJ_SPHERE)
		return (get_sphere_intersect_dist(object, origin, direction));
	else if (object->type == RAYOBJ_PLANE)
		return (get_plane_intersect_dist(object, origin, direction));
	else if (object->type == RAYOBJ_CYLINDER)
		return (get_cylinder_intersect_dist(object, origin, direction));
	else
		return (-1);
}

t_vec3d			get_intersect_normal(t_ray_object *object, t_vec3d intersect)
{
	//if (object->type == RAYOBJ_SPHERE || object->type == RAYOBJ_CYLINDER)
	//	intersect = intersect;
	if (object->type == RAYOBJ_PLANE)
		intersect = vec3d_scalar(object->normal, -1);
	if (object->type == RAYOBJ_CYLINDER)
		intersect.z = 0;
	return (vec3d_unit(intersect));
}
