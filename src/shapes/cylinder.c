/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:28:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/02 15:03:29 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

t_vec3d	get_cylinder_normal(t_ray_object *object, t_vec3d intersect)
{
	(void)object;
	intersect.z = .0;
	return (vec3d_unit(intersect));
}

double	get_cylinder_dist(t_ray_object *object, t_vec3d origin
		, t_vec3d direction)
{
	t_quad	quad;

	quad.a = pow(direction.x, 2) + pow(direction.y, 2);
	quad.b = 2 * (direction.x * origin.x + direction.y * origin.y);
	quad.c = pow(origin.x, 2) + pow(origin.y, 2) - pow(object->radius, 2);
	solve_quadratic_equation(&quad);
	return (add_limit_to_object(object, quad, origin, direction));
}
