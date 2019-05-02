/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:33:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 21:31:35 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

double	get_hyperboloid_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction, double *side)
{
	t_quad	quad;
	double	result;

	quad.a = pow(direction.x, 2) + pow(direction.y, 2) - pow(direction.z, 2);
	quad.b = 2 * (origin.x * direction.x + origin.y * direction.y
			- origin.z * direction.z);
	quad.c = pow(origin.x, 2) + pow(origin.y, 2) - pow(origin.z, 2)
		+ object->radius;
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

t_vec3d	get_hyperboloid_normal(t_ray_object *object, t_vec3d intersect
	, double side)
{
	(void)object;
	intersect.z = -intersect.z;
	if (side == -1.0)
		return (vec3d_unit(vec3d_scalar(intersect, -1)));
	return (vec3d_unit(intersect));
}
