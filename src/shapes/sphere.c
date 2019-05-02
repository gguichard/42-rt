/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:27:31 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 21:31:44 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

t_vec3d	get_sphere_normal(t_ray_object *object, t_vec3d intersect, double side)
{
	(void)object;
	if (side == -1)
		return (vec3d_unit(vec3d_scalar(intersect, -1)));
	return (vec3d_unit(intersect));
}

double	get_sphere_dist(t_ray_object *object, t_vec3d origin, t_vec3d direction
	, double *side)
{
	t_quad	quad;
	double	result;

	quad.a = vec3d_length2(direction);
	quad.b = 2 * vec3d_dot(origin, direction);
	quad.c = vec3d_length2(origin) - pow(object->radius, 2);
	solve_quadratic_equation(&quad);
	result = add_limit_to_object(object, quad, origin, direction);
	if (result > 0)
	{
		if (quad.t1 < 0)
			*side = 1;
		else if (quad.t1 > 0 && result == quad.t2)
			*side = 1;
		else
			*side = -1;
	}
	return (result);
}
