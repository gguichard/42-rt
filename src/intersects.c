#include <math.h>
#include "ray_object.h"
#include "solver.h"
#include "libft.h"
#include "vec3d.h"
#include "ray_inf.h"

static t_vec3d	get_intersect_normal_torus(t_ray_object *object
		, t_vec3d intersect)
{
	t_vec3d		tmp;
	double		a;
	double		b;

	a = pow(object->big_radius, 2);
	b = pow(intersect.x, 2) + pow(intersect.y, 2) + pow(intersect.z, 2)
		- pow(object->radius, 2) + a;
	tmp.x = 4 * intersect.x * b - 8 * a * intersect.x;
	tmp.y = 4 * intersect.y * b;
	tmp.z = 4 * intersect.z * 6 - 8 * a * intersect.z;
	return (vec3d_unit(tmp));
}

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
	t_quad	quad;
	double	cos_r2;

	cos_r2 = pow(cos(object->radius), 2);
	quad.a = pow(direction.z, 2) - cos_r2;
	quad.b = 2 * (direction.z * origin.z - vec3d_dot(direction, origin)
			* cos_r2);
	quad.c = pow(origin.z, 2) - vec3d_length2(origin) * cos_r2;
	return (solve_quadratic_equation(&quad));
}

static double	get_torus_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quartic	quartic;
	double		tmp[3];

	quartic.tmp1 = vec3d_length2(direction);
	quartic.tmp2 = vec3d_dot(direction, origin);
	quartic.tmp3 = vec3d_length2(origin);
	tmp[0] = pow(object->big_radius, 2);
	tmp[1] = pow(object->radius, 2);
	tmp[2] = tmp[0] + tmp[1];
	quartic.a = pow(quartic.tmp1, 2);
	quartic.b = 4 * quartic.tmp1 * quartic.tmp2;
	quartic.c = 2 * quartic.tmp1 * (quartic.tmp3 - tmp[2]) + 4 * pow(quartic.tmp2, 2) + 4 * tmp[0] * pow(direction.y, 2);
	quartic.d = 4 * (quartic.tmp3 - tmp[2]) * quartic.tmp2 + 8 * tmp[0] * (origin.y * direction.y);
	quartic.e = pow(quartic.tmp3 - tmp[2], 2) - 4 * tmp[0] * (tmp[1] - pow(origin.y, 2));
	return (solve_quartic_equation(&quartic));
}

static double	get_sphere_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;

	quad.a = vec3d_length2(direction);
	quad.b = 2 * vec3d_dot(origin, direction);
	quad.c = vec3d_length2(origin) - pow(object->radius, 2);
	return (solve_quadratic_equation(&quad));
}

static double	get_cylinder_intersect_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;
	double	t_min;
	/*double	z1;
	  double	z2;
	  double	tmp;*/

	quad.a = pow(direction.x, 2) + pow(direction.y, 2);
	quad.b = 2 * (direction.x * origin.x + direction.y * origin.y);
	quad.c = pow(origin.x, 2) + pow(origin.y, 2) - pow(object->radius, 2);
	t_min = solve_quadratic_equation(&quad);
	/*if (t_min < 0)
	  return (-1);
	  else if (object->length != 0)
	  {
	  if (quad.t1 > quad.t2)
	  {
	  tmp = quad.t1;
	  quad.t1 = quad.t2;
	  quad.t2 = tmp;
	  }
	  z1 = origin.z + quad.t1 * direction.z;
	  z2 = origin.z + quad.t2 * direction.z;
	  if ((z1 < 0 && z2 < 0) || (z1 > object->length && z2 > object->length))
	  return (-1);
	  else if (z1 < 0 && z2 >= 0)
	  return (quad.t1 + (quad.t2 - quad.t1) * z1 / (z1 - z2));
	  else if (z1 > object->length && z2 <= object->length)
	  return (quad.t1 + (quad.t2 - quad.t1) * (z1 - object->length) / (z1 - z2));
	  }*/
	return (t_min);
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
	else if (object->type == RAYOBJ_TORUS)
		return (get_torus_intersect_dist(object, origin, direction));
	else
		return (-1);
}

t_vec3d			get_intersect_normal(t_ray_object *object, t_vec3d intersect)
{
	if (object->type == RAYOBJ_TORUS)
		return (get_intersect_normal_torus(object, intersect));
	if (object->type == RAYOBJ_PLANE)
		intersect = (t_vec3d){0, 1, 0};
	else if (object->type == RAYOBJ_CYLINDER || object->type == RAYOBJ_CONE)
		intersect.z = .0;
	return (vec3d_unit(intersect));
}
