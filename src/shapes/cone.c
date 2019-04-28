/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/28 16:28:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

t_vec3d	get_cone_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	intersect.z = .0;
	return (vec3d_unit(intersect));
}

double	get_cone_dist(t_ray_object *object, t_vec3d origin, t_vec3d direction)
{
	t_quad	quad;
	double	cos_r2;

	cos_r2 = pow(cos(object->angle), 2);
	quad.a = pow(direction.z, 2) - cos_r2;
	quad.b = 2 * (direction.z * origin.z - vec3d_dot(direction, origin)
			* cos_r2);
	quad.c = pow(origin.z, 2) - vec3d_length2(origin) * cos_r2;
	return (solve_quadratic_equation(&quad));
}
