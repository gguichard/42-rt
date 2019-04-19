/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:24:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/19 12:51:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "ray_inf.h"
#include "calcul.h"
#include "libft.h"

t_vec3d	get_intersect_normal(t_ray_inf *ray_inf, t_vec3d intersect)
{
	return ((t_vec3d){(intersect.x - ray_inf->object->origin.x) / ray_inf->object->radius
			, (intersect.y - ray_inf->object->origin.y) / ray_inf->object->radius
			, (intersect.z - ray_inf->object->origin.z) / ray_inf->object->radius});
}

double	get_sphere_intersect_dist(t_ray_object *object, t_ray_inf *ray_inf)
{
	t_calcul	calc;

	ft_memset(&calc, 0, sizeof(t_calcul));
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
	calc.delta = pow(calc.b, 2) - 4 * calc.a * calc.c;
	if (calc.delta >= 0)
	{
		calc.a = 2 * calc.a;
		calc.tmp3 = sqrt(calc.delta);
		calc.tmp1 = (calc.tmp3 - calc.b) / (calc.a);
		calc.tmp2 = (calc.delta == 0 ? calc.tmp1
				: (-calc.b - calc.tmp3) / (calc.a));
		if (calc.tmp1 >= 0 && calc.tmp2 >= 0)
			return (calc.tmp1 < calc.tmp2 ? calc.tmp1 : calc.tmp2);
		else if (calc.tmp1 >= 0 && calc.tmp2 < 0)
			return (calc.tmp1);
		else if (calc.tmp1 < 0 && calc.tmp2 >= 0)
			return (calc.tmp2);
	}
	return (-1);
}
