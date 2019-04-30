/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/04/30 07:29:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

t_vec3d	get_cone_normal(t_ray_object *object, t_vec3d intersect)
{
	intersect.z = -pow(tan(object->angle), 2);
	return (vec3d_unit(intersect));
}

double	get_cone_dist(t_ray_object *object, t_vec3d origin, t_vec3d direction)
{
	t_quad	quad;
	double	tan_r2;

	tan_r2 = pow(tan(object->angle), 2);
	quad.a = pow(direction.x, 2) + pow(direction.y, 2)
		- pow(direction.z, 2) * tan_r2;
	quad.b = 2 * (direction.x * origin.x + direction.y * origin.y
			- direction.z * origin.z * tan_r2);
	quad.c = pow(origin.x, 2) + pow(origin.y, 2) - pow(origin.z, 2) * tan_r2;
	return (solve_quadratic_equation(&quad));
}
