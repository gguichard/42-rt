/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:32:02 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 15:03:43 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

t_vec3d	get_ellipsoid_normal(t_ray_object *object, t_vec3d intersect)
{
	intersect.x /= (object->size.x * object->size.x);
	intersect.y /= (object->size.y * object->size.y);
	intersect.z /= (object->size.z * object->size.z);
	return (vec3d_unit(intersect));
}

double	get_ellipsoid_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;
	double	tmp[3];

	tmp[0] = pow(object->size.x, 2);
	tmp[1] = pow(object->size.y, 2);
	tmp[2] = pow(object->size.z, 2);
	quad.a = pow(direction.x, 2) / tmp[0] + pow(direction.y, 2) / tmp[1]
		+ pow(direction.z, 2) / tmp[2];
	quad.b = (2 * origin.x * direction.x) / tmp[0]
		+ (2 * origin.y * direction.y) / tmp[1]
		+ (2 * origin.z * direction.z) / tmp[2];
	quad.c = pow(origin.x, 2) / tmp[0] + pow(origin.y, 2) / tmp[1]
		+ pow(origin.z, 2) / tmp[2] - 1;
	solve_quadratic_equation(&quad);
	return (add_limit_to_object(object, quad, origin, direction));
}
