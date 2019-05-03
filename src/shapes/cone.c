/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 16:25:25 by gguichar          #+#    #+#             */
/*   Updated: 2019/05/03 01:15:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray_object.h"
#include "vec3d.h"
#include "solver.h"

static t_vec3d	get_cone_normal(t_ray_object *object, t_ray_hit *hit)
{
	t_vec3d	normal;

	normal = vec3d_add(hit->origin, vec3d_scalar(hit->direction, hit->dist));
	normal.z = -pow(tan(object->angle), 2);
	return (vec3d_unit(normal));
}

void			get_cone_dist(t_ray_object *object, t_ray_hit *hit)
{
	t_quad	quad;
	double	tan_r2;

	tan_r2 = pow(tan(object->angle), 2);
	quad.a = pow(hit->direction.x, 2) + pow(hit->direction.y, 2)
		- pow(hit->direction.z, 2) * tan_r2;
	quad.b = 2 * (hit->direction.x * hit->origin.x
			+ hit->direction.y * hit->origin.y
			- hit->direction.z * hit->origin.z * tan_r2);
	quad.c = pow(hit->origin.x, 2) + pow(hit->origin.y, 2)
		- pow(hit->origin.z, 2) * tan_r2;
	solve_quadratic_equation(&quad);
	hit->dist = add_limit_to_object(object, quad, hit);
	hit->inside = hit->dist > 0 && quad.t1 >= 0 && hit->dist != quad.t2;
	hit->normal = get_cone_normal(object, hit);
}
