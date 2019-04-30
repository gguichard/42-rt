/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:33:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/30 07:30:49 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

double	get_hyperboloid_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;

	quad.a = pow(direction.x, 2) + pow(direction.y, 2) - pow(direction.z, 2);
	quad.b = 2 * (origin.x * direction.x + origin.y * direction.y
			- origin.z * direction.z);
	quad.c = pow(origin.x, 2) + pow(origin.y, 2) - pow(origin.z, 2)
		+ object->radius;
	return (solve_quadratic_equation(&quad));
}

t_vec3d	get_hyperboloid_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	intersect.z = -intersect.z;
	return (vec3d_unit(intersect));
}
