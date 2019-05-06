/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:33:29 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/06 00:01:43 by roduquen         ###   ########.fr       */
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

void			hit_hyperboloid(t_ray_object *object, t_ray_hit *hit)
{
	hit->quad.a = pow(hit->direction.x, 2) + pow(hit->direction.y, 2)
		- pow(hit->direction.z, 2);
	hit->quad.b = 2 * (hit->origin.x * hit->direction.x
			+ hit->origin.y * hit->direction.y
			- hit->origin.z * hit->direction.z);
	hit->quad.c = pow(hit->origin.x, 2) + pow(hit->origin.y, 2)
		- pow(hit->origin.z, 2) + object->radius;
	solve_quadratic_equation(&hit->quad);
	hit->dist = add_limit_to_object(object, hit->quad, hit);
	hit->normal = get_hyperboloid_normal(object, hit);
	hit->inside = hit->dist > 0 && hit->dist == hit->quad.t1;
}
