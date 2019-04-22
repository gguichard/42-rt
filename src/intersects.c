#include <math.h>
#include "ray_object.h"
#include "solver.h"
#include "libft.h"
#include "vec3d.h"

static double	get_plane_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	double	distance;

	(void)object;
	if (fabs(direction.y) > 1e-6)
	{
		distance = origin.y / -direction.y;
		if (distance >= .0)
			return (distance);
	}
	return (-1);
}

static double	get_cone_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	double	cos_r2;
	double	a;
	double	b;
	double	c;

	cos_r2 = pow(cos(object->radius), 2);
	a = pow(direction.z, 2) - cos_r2;
	b = 2 * (direction.z * origin.z - vec3d_dot(direction, origin) * cos_r2);
	c = pow(origin.z, 2) - vec3d_length2(origin) * cos_r2;
	return (solve_quadratic_equation(a, b, c));
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
	else if (object->type == RAYOBJ_CONE)
		return (get_cone_intersect_dist(object, origin, direction));
	else
		return (-1);
}

t_vec3d			get_intersect_normal(t_ray_object *object, t_vec3d intersect)
{
	if (object->type == RAYOBJ_PLANE)
		intersect = (t_vec3d){0, 1, 0};
	else if (object->type == RAYOBJ_CYLINDER || object->type == RAYOBJ_CONE)
		intersect.z = .0;
	return (vec3d_unit(intersect));
}
