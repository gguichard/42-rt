#include <math.h>
#include "ray_object.h"
#include "ray_inf.h"
#include "solver.h"
#include "libft.h"
#include "vec3d.h"
#include <stdio.h>

t_vec3d	get_intersect_normal(t_ray_inf *ray_inf, t_vec3d intersect)
{
	if (ray_inf->object->type == RAYOBJ_SPHERE)
		return (vec3d_unit(vec3d_sub(intersect, ray_inf->object->origin)));
	if (ray_inf->object->type == RAYOBJ_PLANE)
		return (vec3d_unit(ray_inf->origin));
	if (ray_inf->object->type == RAYOBJ_CYLINDER)
		return (vec3d_unit(vec3d_sub(intersect, ray_inf->object->origin)));
	return (vec3d_unit(vec3d_cross_product(ray_inf->object->rotation
					, ray_inf->object->origin)));
}

double	get_torus_intersect_dist(t_ray_object *object, t_ray_inf *ray_inf)
{
	t_compute	calc;
	double		tmp[3];

	calc.tmp1 = vec3d_dot_product(ray_inf->direction, ray_inf->direction);
	calc.tmp2 = vec3d_dot_product(ray_inf->direction, ray_inf->origin);
	calc.tmp3 = vec3d_dot_product(ray_inf->origin, ray_inf->origin);
	tmp[0] = pow(object->big_radius, 2);
	tmp[1] = pow(object->radius, 2);
	tmp[2] = tmp[0] + tmp[1];
	calc.a = pow(calc.tmp1, 2);
	calc.b = 4 * calc.tmp1 * calc.tmp2;
	calc.c = 2 * calc.tmp1 * (calc.tmp3 - tmp[2]) + 4 * pow(calc.tmp2, 2)
		+ 4 * tmp[0] * pow(ray_inf->direction.y, 2);
	calc.d = 4 * (calc.tmp3 - tmp[2]) * calc.tmp2 + 8 * tmp[0]
		* (ray_inf->origin.y * ray_inf->direction.y);
	calc.e = pow(calc.tmp3 - tmp[2], 2) - 4 * tmp[0] * (tmp[1]
			- pow(ray_inf->origin.y, 2));
	return (solve_four_degrees_equation((t_vec3d){calc.a, calc.b, calc.c}
				, calc.d, calc.e));
}

double	get_cone_intersect_dist(t_ray_object *object, t_ray_inf *ray_inf)
{
	t_compute	calc;
	t_vec3d		tmp;

	calc.tmp1 = vec3d_dot_product(ray_inf->direction, object->rotation);
	tmp = vec3d_sub(ray_inf->origin, object->origin);
	calc.tmp2 = vec3d_dot_product(tmp, object->rotation);
	calc.tmp3 = pow(cos(object->radius), 2);
	calc.a = pow(calc.tmp1, 2) - calc.tmp3;
	calc.b = 2 * (calc.tmp1 * calc.tmp2 - vec3d_dot_product(ray_inf->direction
				, tmp) * calc.tmp3);
	calc.c = pow(calc.tmp2, 2) - vec3d_dot_product(tmp, tmp) * calc.tmp3;
	return (solve_quadratic_equation(calc.a, calc.b, calc.c));
}

double	get_plane_intersect_dist(t_ray_object *object, t_ray_inf *ray_inf)
{
	t_compute	calc;
	t_vec3d		tmp;

	object->origin = vec3d_unit(object->origin);
	if ((calc.tmp1 = vec3d_dot_product(object->origin, ray_inf->direction))
		== 0)
		return (-1);
	calc.tmp2 = (vec3d_dot_product(object->origin, ray_inf->origin)
		+ object->radius) / calc.tmp1;
	calc.a = ray_inf->origin.x - calc.tmp2 * ray_inf->direction.x;
	calc.b = ray_inf->origin.y - calc.tmp2 * ray_inf->direction.y;
	calc.c = ray_inf->origin.z - calc.tmp2 * ray_inf->direction.z;
	tmp = (t_vec3d){calc.a - ray_inf->origin.x, calc.b
		- ray_inf->origin.y, calc.c - ray_inf->origin.z};
	calc.tmp2 = vec3d_length(tmp);
	if (calc.tmp2 == 0)
		return (-1);
	if ((calc.tmp1 = vec3d_length(vec3d_add(tmp, ray_inf->direction))) <= calc.tmp2)
		return (-1);
	if (calc.tmp1 < 1)
		return (-1);
	return (calc.tmp2);
}

double	get_sphere_intersect_dist(t_ray_object *object, t_ray_inf *ray_inf)
{
	t_compute	calc;

	calc.tmp1 = ray_inf->origin.x - object->origin.x;
	calc.tmp2 = ray_inf->origin.y - object->origin.y;
	calc.tmp3 = ray_inf->origin.z - object->origin.z;
	calc.a = pow(ray_inf->direction.x, 2) + pow(ray_inf->direction.y, 2)
		+ pow(ray_inf->direction.z, 2);
	calc.b = 2 * (ray_inf->direction.x * calc.tmp1
			+ ray_inf->direction.y * calc.tmp2
			+ ray_inf->direction.z * calc.tmp3);
	calc.c = (pow(calc.tmp1, 2) + pow(calc.tmp2, 2) + pow(calc.tmp3, 2))
		- pow(object->radius, 2);
	return (solve_quadratic_equation(calc.a, calc.b, calc.c));
}

double	get_cylinder_intersect_dist(t_ray_object *object, t_ray_inf *ray_inf)
{
	t_compute	calc;

	calc.tmp1 = ray_inf->origin.x - object->origin.x;
	calc.tmp2 = ray_inf->origin.y - object->origin.y;
	calc.a = pow(ray_inf->direction.x, 2) + pow(ray_inf->direction.y, 2);
	calc.b = 2 * (ray_inf->direction.x * calc.tmp1
		+ ray_inf->direction.y * calc.tmp2);
	calc.c = (pow(calc.tmp1, 2) + pow(calc.tmp2, 2)) - pow(object->radius, 2);
	return (solve_quadratic_equation(calc.a, calc.b, calc.c));
}
