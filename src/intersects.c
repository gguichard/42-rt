#include <math.h>
#include "ray_object.h"
#include "ray_inf.h"
#include "solver.h"
#include "libft.h"

t_vec3d	get_intersect_normal(t_ray_inf *ray_inf, t_vec3d intersect)
{
	return (vec3d_unit(vec3d_sub(intersect, ray_inf->object->origin)));
}

double	get_plane_intersect_dist(t_ray_object *object, t_ray_inf *ray_inf)
{
	t_compute	calc;
	t_vec3d		tmp;

	ft_memset(&calc, 0, sizeof(t_compute));
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
	if (vec3d_length(vec3d_add(tmp, ray_inf->direction)) <= calc.tmp2)
		return (-1);
	return (calc.tmp2);
}

double	get_sphere_intersect_dist(t_ray_object *object, t_ray_inf *ray_inf)
{
	t_compute	calc;

	ft_memset(&calc, 0, sizeof(t_compute));
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

	ft_memset(&calc, 0, sizeof(t_compute));
	calc.tmp1 = ray_inf->origin.x - object->origin.x;
	calc.tmp2 = ray_inf->origin.y - object->origin.y;
	calc.a = pow(ray_inf->direction.x, 2) + pow(ray_inf->direction.y, 2);
	calc.b = 2 * (ray_inf->direction.x * calc.tmp1
		+ ray_inf->direction.y * calc.tmp2);
	calc.c = (pow(calc.tmp1, 2) + pow(calc.tmp2, 2)) - pow(object->radius, 2);
	return (solve_quadratic_equation(calc.a, calc.b, calc.c));
}
