/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:33:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 01:57:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_hyperboloid_normal(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	normal;

	(void)object;
	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, hit->dist));
	normal.z = -normal.z;
	return (vec3d_unit(normal));
}

void			get_hyperboloid_dist(t_ray_object *object, t_ray_hit *hit)
{
	t_quad	quad;

	quad.a = pow(hit->direction.x, 2) + pow(hit->direction.y, 2)
		- pow(hit->direction.z, 2);
	quad.b = 2 * (hit->origin.x * hit->direction.x
			+ hit->origin.y * hit->direction.y
			- hit->origin.z * hit->direction.z);
	quad.c = pow(hit->origin.x, 2) + pow(hit->origin.y, 2)
		- pow(hit->origin.z, 2) + object->radius;
	solve_quadratic_equation(&quad);
	hit->dist = add_limit_to_object(object, quad, hit);
	hit->normal = get_hyperboloid_normal(object, hit);
	hit->inside = hit->dist > 0 && quad.t1 >= 0 && hit->dist != quad.t2;
}
